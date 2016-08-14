#ifndef _OSGVIEWER_VIEW_QTQUICK_INDEX_
#define _OSGVIEWER_VIEW_QTQUICK_INDEX_ 1

#include <osgQtQuick/Index>
#include <osgQtQuick/Window>

#include <osg/Camera>
#include <osgViewer/ViewQtQuick>

#include <QOpenGLFramebufferObject>
#include <QSGSimpleTextureNode>
#include <QMutex>

namespace osgQtQuick {
class Window;
class RenderThread;
}

namespace osgViewer {

class OSGQTQUICK_EXPORT ViewQtQuick::Index : public osgQtQuick::Index
{
public:
    typedef View OType;
    typedef ViewQtQuick QType;
    friend class ViewQtQuick;

    struct PreDraw: public osg::Camera::DrawCallback {
    public:
        PreDraw(Index *i);

        void operator ()(osg::RenderInfo &renderInfo) const;

        mutable Index *i;
    };

    struct PostDraw: public osg::Camera::DrawCallback {
    public:
        PostDraw(Index *i);

        void operator ()(osg::RenderInfo &renderInfo) const;

        mutable Index *i;
    };

public:
    Index(View *o = 0);
    ~Index();

    osg::NodeQtQml* getSceneData();
    void setSceneData(osg::NodeQtQml *node);

    osg::CameraQtQml* getCamera();
    void setCamera(osg::CameraQtQml *camera);

    osgGA::CameraManipulatorQtQml* getCameraManipulator();
    void setCameraManipulator(osgGA::CameraManipulatorQtQml *manipulator);

    void prepareNode();

    void classBegin();

protected:
    void setKeyboardModifiers(QInputEvent* event);
    int  mouseButton(QMouseEvent* event);
    QPointF mousePoint(QMouseEvent* event);

    void mouseButtonPress(QMouseEvent *event);
    void mouseMotion(QMouseEvent *event);
    void mouseButtonRelease(QMouseEvent *event);
    void mouseDoubleButtonPress(QMouseEvent *event);

    void prepareObject();
    void deleteFrameBufferObjects();
    void updateViewport();
    void acceptWindow(osgQtQuick::Window *window);

private:
    friend class osgQtQuick::Window;
    friend class osgQtQuick::RenderThread;

    osgQtQuick::Window *window;
    QOpenGLFramebufferObjectFormat format;
    QOpenGLFramebufferObject *renderFbo, *displayFbo;
    QSGTexture *renderTexture, *displayTexture;
    QSGSimpleTextureNode *textureNode;
    osg::ref_ptr<osg::GraphicsContext> context;
    osg::ref_ptr<PreDraw> preDraw;
    osg::ref_ptr<PostDraw> postDraw;
    struct {
        int update;
        QSize size;
    } display;
    struct {
        int update;
        QSize size;
    } render;
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_INDEX_
