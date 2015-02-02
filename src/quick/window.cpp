#include "window.hpp"
#include "index.hpp"

#include <osg/GraphicsContextQtQml>
#include <osgViewer/CompositeViewerQtQml>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QTimerEvent>

namespace osgQtQuick {

Window::Window(QQuickWindow *window) :
    QObject(window)
{
    osgQtQuick::Index::storage.windows.insert(
                std::pair<QQuickWindow*, Window*>(window, this));

    d.window = window;

    connect(window, SIGNAL(beforeRendering()), this, SLOT(frame()));

    // Render loop
    d.window->setClearBeforeRendering(false);
    d.frameTimer = startTimer(10);

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
}

Window::~Window()
{
    osgQtQuick::Index::storage.windows.erase(d.window);
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
    // Qt bug!?
    QOpenGLContext::currentContext()->functions()->glUseProgram(0);

    d.viewer->frame();
}

void Window::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == d.frameTimer) {
        if (d.window) d.window->update();
    }

    QObject::timerEvent(event);
}

} // namespace osgQtQuick

