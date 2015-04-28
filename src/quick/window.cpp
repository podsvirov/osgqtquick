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

    connect(window, SIGNAL(beforeRendering()), this, SLOT(frame()), Qt::DirectConnection);

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
#if 0
    // Qt bug!?
    QOpenGLContext::currentContext()->functions()->glUseProgram(0);

    d.viewer->frame();
#endif
#if 1
    // save the current context
    // note: this will save only Qt-based contexts
    const QOpenGLContext*savedContext = QOpenGLContext::currentContext();
    QSurface* savedSurface = QOpenGLContext::currentContext()->surface();

    // Qt bug!?
    QOpenGLContext::currentContext()->functions()->glUseProgram(0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //char* version = (char*)glGetString(GL_VERSION);

//    if( callFrame ) d.viewer->frame();
    d.viewer->frame();

graphicsContext()->getState()->dirtyAllModes();//
graphicsContext()->getState()->dirtyAllAttributes();
graphicsContext()->getState()->dirtyAllVertexArrays();

graphicsContext()->getState()->disableAllVertexArrays();//
graphicsContext()->getState()->disableVertexPointer();
graphicsContext()->getState()->disableTexCoordPointersAboveAndIncluding(0);//
graphicsContext()->getState()->disableVertexAttribPointersAboveAndIncluding(0);
graphicsContext()->getState()->disableColorPointer();
graphicsContext()->getState()->disableFogCoordPointer();
graphicsContext()->getState()->disableNormalPointer();
graphicsContext()->getState()->disableSecondaryColorPointer();

/*
    // qpainter uses vertex attribs 3,4,5 so we need to explicitly disable them:
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(0);
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(1);
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(2);
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(3); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(4); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(5); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(6); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(7); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(8); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(9); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(10); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(11); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(12); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(13); 
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(14);
    QOpenGLContext::currentContext()->functions()->glDisableVertexAttribArray(15); 
*/

    // not sure if this is required; osg changes this when using textures so I reset it to default 
    glPixelStorei(GL_UNPACK_ALIGNMENT,4); 

    glPopAttrib();

    // restore previous context
    if ( savedContext )
        const_cast< QOpenGLContext* >( savedContext )->makeCurrent(savedSurface);
#endif
}

void Window::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == d.frameTimer) {
        if (d.window) d.window->update();
    }

    QObject::timerEvent(event);
}

} // namespace osgQtQuick

