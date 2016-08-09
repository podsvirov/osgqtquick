#ifndef _OSGVIEWER_VIEW_QTQUICK_INDEX_
#define _OSGVIEWER_VIEW_QTQUICK_INDEX_ 1

#include <osgQtQuick/Index>
#include <osgQtQuick/Window>

#include <osg/Camera>
#include <osgViewer/ViewQtQuick>

#include <QOpenGLFramebufferObject>
#include <QSGSimpleTextureNode>
#include <QMutex>

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


    void initFBO();
    void updateFBO();
    void prepareObject();
    void updateViewport();
    void acceptWindow(osgQtQuick::Window *window);

private:
    QSize size;
    osgQtQuick::Window *window;
    QOpenGLFramebufferObjectFormat format;
    QOpenGLFramebufferObject *renderFbo, *displayFbo;
    int needUpdate;
    QMutex needUpdateFboMutex;
    QSGTexture *renderTexture, *displayTexture;
    QSGSimpleTextureNode *textureNode;
    osg::ref_ptr<osg::GraphicsContext> context;
    osg::ref_ptr<PreDraw> preDraw;
    osg::ref_ptr<PostDraw> postDraw;
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_INDEX_
