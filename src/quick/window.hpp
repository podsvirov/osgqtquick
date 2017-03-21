#ifndef _OSGQTQUICK_WINDOW_
#define _OSGQTQUICK_WINDOW_ 1

#include <osgQtQuick/Export>

#include <QtQuick/QQuickWindow>

#include <osgViewer/CompositeViewer>
#include <osgViewer/GraphicsWindow>

#include <osgViewer/ViewQtQuick>

#include <set>

namespace osgQtQuick {

enum RenderLoopType {
    BasicRenderLoop,
    ThreadedRenderLoop,
    WindowsRenderLoop
};

class RenderThread;

class OSGQTQUICK_EXPORT Window : public QObject
{
    Q_OBJECT

public:
    Window(QQuickWindow *window);
    ~Window();

    osgViewer::CompositeViewer* viewer();
    osg::GraphicsContext* graphicsContext();

    RenderLoopType renderLoopType();
    RenderThread* renderThread();

    QQuickWindow* quickWindow();

    int minFrameTime();

    void addView(osgViewer::ViewQtQuick::Index *view);
    void removeView(osgViewer::ViewQtQuick::Index *view);

    static Window * fromWindow(QQuickWindow *window);

Q_SIGNALS:
    void textureInUse();
    void acceptNewSize(osgViewer::ViewQtQuick::Index *view, QSize size);
    void pendingNewTexture();

public Q_SLOTS:
    void frame();
    void ready(); // Context ready for rendering
    void prepareNodes();
    void deleteFbos();
    void newTexture();
    void onSceneGraphAboutToStop();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void timerEvent(QTimerEvent *event);

private:
  friend class osgViewer::ViewQtQuick;
  friend class osgViewer::ViewQtQuick::Index;

  struct {
    QQuickWindow *window;
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> context;
    osg::ref_ptr<osgViewer::CompositeViewer> viewer;
    std::set<osgViewer::ViewQtQuick::Index*> views;
    int frameTimer;
    int minFrameTime;
    RenderLoopType renderLoopType;
    RenderThread *renderThread;
    bool newTexture;
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

inline int Window::minFrameTime()
{
    return d.minFrameTime;
}

} // namespace osgQtQuick

#endif // _OSGQTQUICK_WINDOW_
