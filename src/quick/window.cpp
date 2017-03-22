#include "window.hpp"
#include "index.hpp"
#include "renderthread.hpp"

#include <osg/GraphicsContextQtQml>
#include <osgViewer/CompositeViewerQtQml>
#include <osgViewer/ViewQtQuickIndex>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QTimerEvent>

#ifdef OSGQTQUICK_WITH_QT_PRIVATE

#include <private/qqmlglobal_p.h>
#include <private/qguiapplication_p.h>
#include <qpa/qplatformintegration.h>

#endif // OSGQTQUICK_WITH_QT_PRIVATE

#include <iostream>

namespace osgQtQuick {

#ifdef OSGQTQUICK_WITH_QT_PRIVATE

DEFINE_BOOL_CONFIG_OPTION(qmlNoThreadedRenderer, QML_BAD_GUI_RENDER_LOOP);
DEFINE_BOOL_CONFIG_OPTION(qmlForceThreadedRenderer, QML_FORCE_THREADED_RENDERER);

#endif // OSGQTQUICK_WITH_QT_PRIVATE

Window::Window(QQuickWindow *window) :
    QObject(window)
{
    d.window = window;

    d.frameTimer = -1;
    d.newTexture = false;
    d.renderThread = 0;

    osgQtQuick::Index::storage.windows.insert(
                std::pair<QQuickWindow*, Window*>(window, this));

    // Detect render loop type
    d.renderLoopType = BasicRenderLoop;
    {
        // This code block has been coped from QT_DECLARATIVE_ROOT_DIR/srd/quick/scenegraph/qsgrenderloop.cpp

        RenderLoopType &renderLoopType = d.renderLoopType;

#ifdef OSGQTQUICK_WITH_QT_PRIVATE

#ifdef Q_OS_WIN
        // With desktop OpenGL (opengl32.dll), use threaded. Otherwise (ANGLE) use windows.
        if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL
                && QGuiApplicationPrivate::platformIntegration()->hasCapability(QPlatformIntegration::ThreadedOpenGL))
            renderLoopType = ThreadedRenderLoop;
        else
            renderLoopType = WindowsRenderLoop;
#else
        if (QGuiApplicationPrivate::platformIntegration()->hasCapability(QPlatformIntegration::ThreadedOpenGL))
            renderLoopType = ThreadedRenderLoop;
#endif
        if (qmlNoThreadedRenderer())
            renderLoopType = BasicRenderLoop;
        else if (qmlForceThreadedRenderer())
            renderLoopType = ThreadedRenderLoop;

#endif // OSGQTQUICK_WITH_QT_PRIVATE

        if (Q_UNLIKELY(qEnvironmentVariableIsSet("QSG_RENDER_LOOP"))) {
            const QByteArray loopName = qgetenv("QSG_RENDER_LOOP");
            if (loopName == QByteArrayLiteral("windows"))
                renderLoopType = WindowsRenderLoop;
            else if (loopName == QByteArrayLiteral("basic"))
                renderLoopType = BasicRenderLoop;
            else if (loopName == QByteArrayLiteral("threaded"))
                renderLoopType = ThreadedRenderLoop;
        }
    }

    // Min frame time
    // 17 mc -> 59 fps (< 60 fps)
    // Any timer value less then 17 mc (> 60 fps) is caused bug with camera manipulator in rotating mode
    d.minFrameTime = 17;

    connect(window, SIGNAL(sceneGraphAboutToStop()), this, SLOT(onSceneGraphAboutToStop()));

    if(d.renderLoopType == ThreadedRenderLoop)
    {
        d.renderThread = new RenderThread(this);
        connect(this, SIGNAL(acceptNewSize(osgViewer::ViewQtQuick::Index*, QSize)),
                d.renderThread, SLOT(acceptNewSize(osgViewer::ViewQtQuick::Index*, QSize)));
        connect(d.renderThread, SIGNAL(textureReady()), this, SLOT(newTexture()), Qt::QueuedConnection);
        connect(d.window, SIGNAL(beforeRendering()), this, SLOT(prepareNodes()), Qt::DirectConnection);
        connect(this, SIGNAL(textureInUse()), d.renderThread, SLOT(renderNext()), Qt::QueuedConnection);
        connect(d.renderThread, SIGNAL(textureReady()), window, SLOT(update()), Qt::QueuedConnection);
    }
    else
    {
        connect(d.window, SIGNAL(beforeRendering()), this, SLOT(prepareNodes()), Qt::DirectConnection);
        connect(this, SIGNAL(pendingNewTexture()), window, SLOT(update()), Qt::QueuedConnection);
    }

    // Disable clearing
    d.window->setClearBeforeRendering(false);

    // Context
    d.context = new osgViewer::GraphicsWindowEmbedded(0, 0,
                                                      window->width(),
                                                      window->height());
    osg::GraphicsContextQtQml::fromGraphicsContext(d.context, this);

    // Viewer
    d.viewer = new osgViewer::CompositeViewer();
    d.viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
    // disable the default setting of viewer.done() by pressing Escape.
    d.viewer->setKeyEventSetsDone(0);

    // Handle window events
    window->installEventFilter(this);
}

Window::~Window()
{
    osgQtQuick::Index::storage.windows.erase(d.window);
}

RenderLoopType Window::renderLoopType()
{
    return d.renderLoopType;
}

RenderThread *Window::renderThread()
{
    return d.renderThread;
}

QQuickWindow *Window::quickWindow()
{
    return d.window;
}

void Window::addView(osgViewer::ViewQtQuick::Index *view)
{
    d.viewer->addView(osgViewer::ViewQtQuick::Index::o(view));

    d.views.insert(view);
}

void Window::removeView(osgViewer::ViewQtQuick::Index *view)
{
    d.viewer->removeView(osgViewer::ViewQtQuick::Index::o(view));
    d.views.erase(view);
}

Window *Window::fromWindow(QQuickWindow *window)
{
    if(!window) return 0;

    std::map<QQuickWindow*, Window*>::iterator it =
            osgQtQuick::Index::storage.windows.find(window);

    if(it != osgQtQuick::Index::storage.windows.end()) return it->second;

    return new Window(window);
}

void Window::frame()
{
    if(d.renderLoopType != ThreadedRenderLoop) {
        { // Qt bug!?
            QOpenGLContext::currentContext()->functions()->glUseProgram(0);
        }
        d.viewer->frame();
        d.newTexture = true;
        prepareNodes();
    } else {
        d.viewer->frame();
    }
}

void Window::ready()
{
    if(d.renderLoopType == ThreadedRenderLoop) {

        d.renderThread->surface = new QOffscreenSurface();
        d.renderThread->surface->setFormat(d.renderThread->context->format());
        d.renderThread->surface->create();

        d.renderThread->moveToThread(d.renderThread);

        connect(d.window, SIGNAL(sceneGraphInvalidated()), d.renderThread, SLOT(shutDown()), Qt::QueuedConnection);

        d.renderThread->start();

        QMetaObject::invokeMethod(d.renderThread, "renderNext", Qt::QueuedConnection);

    } else {
        d.frameTimer = startTimer(d.minFrameTime);
    }
}

void Window::prepareNodes()
{
    if(d.newTexture) {
        for(std::set<osgViewer::ViewQtQuick::Index*>::iterator it = d.views.begin();
            it != d.views.end(); ++it) {
            (*it)->prepareNode();
        }
        d.newTexture = false;
        emit textureInUse();
    }
    emit pendingNewTexture();
}

void Window::deleteFbos()
{
    for(std::set<osgViewer::ViewQtQuick::Index*>::iterator it = d.views.begin();
        it != d.views.end(); ++it) {
        (*it)->deleteFrameBufferObjects();
    }
}

void Window::newTexture()
{
    d.newTexture = true;
}

void Window::onSceneGraphAboutToStop()
{
    if(d.frameTimer != -1) {
        killTimer(d.frameTimer);
        d.frameTimer = -1;
    }
}

bool Window::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        QSize size = static_cast<QResizeEvent*>(event)->size();
        d.context->resizedImplementation(0, 0, size.width(), size.height());
    }

    return QObject::eventFilter(watched, event);
}

void Window::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == d.frameTimer) {
        frame();
    }

    QObject::timerEvent(event);
}

} // namespace osgQtQuick

