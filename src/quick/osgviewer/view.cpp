#include "view.hpp"
#include "viewindex.hpp"

#include <osgQtQuick/Window>

#include <osgViewer/View>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <QMouseEvent>
#include <QKeyEvent>

/*!
   \qmltype View
   \inqmlmodule osgViewer
   \brief The View type holds a single view on a scene
 */

namespace osgViewer {

/* ------------------------------------------------------- struct PreDraw --- */

ViewQtQuick::Index::PreDraw::PreDraw(Index *i) : i(i) {
}

void ViewQtQuick::Index::PreDraw::operator ()(osg::RenderInfo &/*renderInfo*/) const
{
    if (!i->fbo) i->initFBO();
    if (i->fbo) i->fbo->bind();
}

/* ------------------------------------------------------ struct PostDraw --- */

ViewQtQuick::Index::PostDraw::PostDraw(Index *i) : i(i) {
}

void ViewQtQuick::Index::PostDraw::operator ()(osg::RenderInfo &/*renderInfo*/) const
{
    if (i->fbo) i->fbo->bindDefault();
}

/* ---------------------------------------------------------- class Index --- */

ViewQtQuick::Index::Index(View *view) :
    osgQtQuick::Index(view)
{
    window = 0;
    fbo = 0;
    texture = 0;
    textureNode = 0;
}

osg::NodeQtQml *ViewQtQuick::Index::getSceneData()
{
    return osg::NodeQtQml::fromNode(o(this)->getSceneData(), q(this));
}

void ViewQtQuick::Index::setSceneData(osg::NodeQtQml *node)
{
    if(getSceneData() == node) return;

    o(this)->setSceneData(node->node());

    emit q(this)->sceneDataChanged(node);
}

/*!
   \qmlproperty osg::Camera osgViewer::View::camera

   Master \l {osg::Camera}{camera} of the view.
 */

osg::CameraQtQml *ViewQtQuick::Index::getCamera()
{
    return osg::CameraQtQml::fromCamera(o(this)->getCamera(), q(this));
}

void ViewQtQuick::Index::setCamera(osg::CameraQtQml *camera)
{
    o(this)->setCamera(camera->camera());
}

osgGA::CameraManipulatorQtQml *ViewQtQuick::Index::getCameraManipulator()
{
    return osgGA::CameraManipulatorQtQml::fromCameraManipulator(o(this)->getCameraManipulator(), q(this));
}

void ViewQtQuick::Index::setCameraManipulator(osgGA::CameraManipulatorQtQml *manipulator)
{
    o(this)->setCameraManipulator(manipulator ? manipulator->cameraManipulator()
                                              : 0);
}

void ViewQtQuick::Index::classBegin()
{
    if(!o(this)) setO(new View);

    q(this)->setAcceptHoverEvents(true);
    q(this)->setAcceptedMouseButtons(Qt::AllButtons);

    preDraw = new PreDraw(this);
    o(this)->getCamera()->setPreDrawCallback(preDraw.get());

    postDraw = new PostDraw(this);
    o(this)->getCamera()->setPostDrawCallback(postDraw.get());

    osgQtQml::Index::classBegin();
}

void ViewQtQuick::Index::setKeyboardModifiers(QInputEvent *event)
{
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    unsigned int mask = 0;
    if ( modkey & Qt::ShiftModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    if ( modkey & Qt::ControlModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    if ( modkey & Qt::AltModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
    o(this)->getEventQueue()->getCurrentEventState()->setModKeyMask( mask );
}

int ViewQtQuick::Index::mouseButton(QMouseEvent *event)
{
    int button = 0;
    switch ( event->button() )
    {
        case Qt::LeftButton: button = 1; break;
        case Qt::MidButton: button = 2; break;
        case Qt::RightButton: button = 3; break;
        case Qt::NoButton: button = 0; break;
        default: button = 0; break;
    }

    return button;
}

QPointF ViewQtQuick::Index::mousePoint(QMouseEvent *event)
{
    qreal x = 2.0 * (event->x() - q(this)->width() / 2) / q(this)->width();
    qreal y = 2.0 * (event->y() - q(this)->height() / 2) / q(this)->height();

    return QPointF(x, y);
}

void ViewQtQuick::Index::mouseButtonPress(QMouseEvent *event)
{
    int button = mouseButton(event);
    setKeyboardModifiers(event);
    QPointF pos = mousePoint(event);
    o(this)->getEventQueue()->mouseButtonPress(pos.x(), pos.y(), button);
}

void ViewQtQuick::Index::mouseMotion(QMouseEvent *event)
{
    setKeyboardModifiers(event);
    QPointF pos = mousePoint(event);
    o(this)->getEventQueue()->mouseMotion(pos.x(), pos.y());
}

void ViewQtQuick::Index::mouseButtonRelease(QMouseEvent *event)
{
    int button = mouseButton(event);
    setKeyboardModifiers(event);
    QPointF pos = mousePoint(event);
    o(this)->getEventQueue()->mouseButtonRelease(pos.x(), pos.y(), button);
}

void ViewQtQuick::Index::mouseDoubleButtonPress(QMouseEvent *event)
{
    int button = mouseButton(event);
    setKeyboardModifiers(event);
    QPointF pos(event->x(), q(this)->height() - event->y());
    o(this)->getEventQueue()->mouseDoubleButtonPress(pos.x(), pos.y(), button);
}

void ViewQtQuick::Index::initFBO()
{
    QRectF rect = q(this)->mapRectToItem(0, q(this)->boundingRect());
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    QSize size(rect.size().toSize());
    fbo = new QOpenGLFramebufferObject(size, format);
    texture = q(this)->window()->createTextureFromId(fbo->texture(), size);
    textureNode = new QSGSimpleTextureNode();
    textureNode->setRect(0, q(this)->height(), q(this)->width(), -q(this)->height());
    textureNode->setTexture(texture);
    q(this)->setFlag(QQuickItem::ItemHasContents, true);
    updateViewport();
    q(this)->update();
}

void ViewQtQuick::Index::updateFBO()
{
    if (fbo) delete fbo;
    QRectF rect = q(this)->mapRectToItem(0, q(this)->boundingRect());
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    QSize size(rect.size().toSize());
    fbo = new QOpenGLFramebufferObject(size, format);
    if (texture) delete texture;
    texture = q(this)->window()->createTextureFromId(fbo->texture(), size);
    textureNode = new QSGSimpleTextureNode();
    textureNode->setRect(0, q(this)->height(), q(this)->width(), -q(this)->height());
    textureNode->setTexture(texture);
    q(this)->update();
}

void ViewQtQuick::Index::updateViewport()
{
    QSize size(q(this)->boundingRect().size().toSize());
    o(this)->getCamera()->setViewport(0, 0, size.width(), size.height());
    o(this)->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(size.width())/static_cast<double>(size.height()), 1.0f, 10000.0f );
    if (texture && texture->textureSize() != size) {
        updateFBO();
    }
}

void ViewQtQuick::Index::acceptWindow(osgQtQuick::Window *window)
{
    o(this)->getCamera()->setGraphicsContext(window->graphicsContext());
    updateViewport();
    window->viewer()->addView(o(this));
}

ViewQtQuick *ViewQtQuick::fromView(View *view, QQuickItem *parent)
{
    if(!view) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(view))
    {
        return static_cast<ViewQtQuick*>(index->qtObject());
    }

    return new ViewQtQuick(new Index(view), parent);
}

void ViewQtQuick::mousePressEvent(QMouseEvent *event)
{
    i(this)->mouseButtonPress(event);
}

void ViewQtQuick::mouseMoveEvent(QMouseEvent *event)
{
    i(this)->mouseMotion(event);
}

void ViewQtQuick::mouseReleaseEvent(QMouseEvent *event)
{
    i(this)->mouseButtonRelease(event);
}

void ViewQtQuick::mouseDoubleClickEvent(QMouseEvent *event)
{
    i(this)->mouseDoubleButtonPress(event);
}

void ViewQtQuick::wheelEvent(QWheelEvent *event)
{
    o(this)->getEventQueue()->mouseScroll(
                event->orientation() == Qt::Vertical ?
                    (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
                    (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT) );
}

void ViewQtQuick::keyPressEvent(QKeyEvent *event)
{
    i(this)->setKeyboardModifiers(event);
    o(this)->getEventQueue()->keyPress( osgQt::swapKey(event) );
}

void ViewQtQuick::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        i(this)->setKeyboardModifiers(event);
        o(this)->getEventQueue()->keyRelease(osgQt::swapKey(event));
    }
}

void ViewQtQuick::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    osgQtQuick::Object::geometryChanged(newGeometry, oldGeometry);

    i(this)->updateViewport();
}

QSGNode *ViewQtQuick::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    if (oldNode && oldNode != i(this)->textureNode) {
        delete oldNode;
    }
    Q_UNUSED(updatePaintNodeData);

    return i(this)->textureNode;
}

void ViewQtQuick::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &value)
{
    if(change == QQuickItem::ItemSceneChange)
    {
        if(osgQtQuick::Window *window =
                osgQtQuick::Window::fromWindow(value.window))
        {
            i(this)->acceptWindow(window);
        }
    }
    osgQtQuick::Object::itemChange(change, value);
}

/*!
   \qmlproperty Node osgViewer::View::sceneData

   The \l {View}'s scene graph
 */

osg::NodeQtQml *ViewQtQuick::getSceneData()
{
    return i(this)->getSceneData();
}

void ViewQtQuick::setSceneData(osg::NodeQtQml *node)
{
    i(this)->setSceneData(node);
}

osg::CameraQtQml *ViewQtQuick::getCamera()
{
    return i(this)->getCamera();
}

void ViewQtQuick::setCamera(osg::CameraQtQml *camera)
{
    i(this)->setCamera(camera);
}

/*!
   \qmlproperty CameraManipulator osgViewer::View::cameraManipulator

   The \l {View}'s CameraManipulator
 */

osgGA::CameraManipulatorQtQml *ViewQtQuick::getCameraManipulator()
{
    return i(this)->getCameraManipulator();
}

void ViewQtQuick::setCameraManipulator(osgGA::CameraManipulatorQtQml *manipulator)
{
    i(this)->setCameraManipulator(manipulator);
}

ViewQtQuick::ViewQtQuick(QQuickItem *parent) :
  osgQtQuick::Object(parent)
{
}

ViewQtQuick::ViewQtQuick(ViewQtQuick::Index *index, QQuickItem *parent) :
  osgQtQuick::Object(index, parent)
{
}

void ViewQtQuick::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgQtQuick::Object::classBegin();
}

void ViewQtQuick::componentComplete()
{
    osgQtQuick::Object::componentComplete();
}

}
