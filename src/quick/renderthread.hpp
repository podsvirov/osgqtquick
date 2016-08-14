#ifndef _OSGQTQUICK_RENDERTHREAD_
#define _OSGQTQUICK_RENDERTHREAD_ 1

#include <osgQtQuick/Export>
#include <osgViewer/ViewQtQuick>

#include <QGuiApplication>
#include <QThread>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOffscreenSurface>
#include <QOpenGLFramebufferObjectFormat>
#include <QDateTime>

namespace osgQtQuick {

class Window;

class OSGQTQUICK_EXPORT RenderThread : public QThread
{
    Q_OBJECT

public:
    RenderThread(Window *window);

    Window *window;
    bool started;

    QOffscreenSurface *surface;
    QOpenGLContext *context;

public slots:
    void renderNext();

    void shutDown();

    void acceptNewSize(osgViewer::ViewQtQuick::Index *view, QSize size);

signals:
    void textureReady();

private:
    QDateTime _latestEndFrameTime;
    bool _shutDown;
};

}

#endif // _OSGQTQUICK_RENDERTHREAD_
