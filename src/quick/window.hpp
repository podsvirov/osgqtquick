#ifndef _OSGQTQUICK_WINDOW_
#define _OSGQTQUICK_WINDOW_ 1

#include <QQuickWindow>

#include <osgViewer/CompositeViewer>
#include <osgViewer/GraphicsWindow>

namespace osgQtQuick {

class Window : public QObject
{
    Q_OBJECT

public:
    Window(QQuickWindow *window);
    ~Window();

    osgViewer::CompositeViewer* viewer();
    osg::GraphicsContext* graphicsContext();

    static Window * fromWindow(QQuickWindow *window);

signals:

public slots:
    void frame(); // frame

protected:
    void timerEvent(QTimerEvent *event);

private:
  struct {
    QQuickWindow *window;
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> context;
    osg::ref_ptr<osgViewer::CompositeViewer> viewer;
    int frameTimer;
  } d;
};

inline osgViewer::CompositeViewer *Window::viewer()
{
    return d.viewer.get();
}

inline osg::GraphicsContext *Window::graphicsContext()
{
    return d.context.get();
}

} // namespace osgQtQuick

#endif // _OSGQTQUICK_WINDOW_
