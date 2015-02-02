#ifndef _OSGVIEWER_VIEW_QTQUICK_INDEX_
#define _OSGVIEWER_VIEW_QTQUICK_INDEX_ 1

#include <osgQtQuick/Index>
#include <osgQtQuick/Window>

#include <osg/Camera>
#include <osgViewer/ViewQtQuick>

#include <QOpenGLFramebufferObject>
#include <QSGSimpleTextureNode>

namespace osgViewer {

class OSGQTQUICK_EXPORT ViewQtQuick::Index : public osgQtQuick::Index
{
public:
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

    osg::NodeQtQml* getSceneData();
    void setSceneData(osg::NodeQtQml *node);

    void classBegin();

protected:
    void setKeyboardModifiers(QInputEvent* event);
    int  mouseButton(QMouseEvent* event);
    QPointF mousePoint(QMouseEvent* event);

    void mouseButtonPress(QMouseEvent *event);
    void mouseMotion(QMouseEvent *event);
    void mouseButtonRelease(QMouseEvent *event);


    void initFBO();
    void updateFBO();
    void updateViewport();
    void acceptWindow(osgQtQuick::Window *window);

private:
    osgQtQuick::Window *window;
    QOpenGLFramebufferObject *fbo;
    QSGTexture *texture;
    QSGSimpleTextureNode *textureNode;
    osg::ref_ptr<PreDraw> preDraw;
    osg::ref_ptr<PostDraw> postDraw;

    View *othis;
    ViewQtQuick *qthis;
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_INDEX_
