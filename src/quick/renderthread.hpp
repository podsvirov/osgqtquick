#ifndef _OSGQTQUICK_RENDERTHREAD_
#define _OSGQTQUICK_RENDERTHREAD_ 1

#include <osgQtQuick/Export>
#include <osgViewer/ViewQtQuick>

#include <QGuiApplication>
#include <QtCore/QThread>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLFramebufferObjectFormat>
#include <QtCore/QDateTime>

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

public Q_SLOTS:
    void renderNext();

    void shutDown();

    void acceptNewSize(osgViewer::ViewQtQuick::Index *view, QSize size);

Q_SIGNALS:
    void textureReady();

private:
    QDateTime _latestEndFrameTime;
    bool _shutDown;
};

}

#endif // _OSGQTQUICK_RENDERTHREAD_
