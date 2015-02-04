#include "view.hpp"
#include "viewindex.hpp"

#include <osgQtQuick/Window>

#include <osgViewer/View>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <QMouseEvent>

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
    othis = view;

    window = 0;
    fbo = 0;
    texture = 0;
    textureNode = 0;
}

osg::NodeQtQml *ViewQtQuick::Index::getSceneData()
{
    return osg::NodeQtQml::fromNode(othis->getSceneData(), qthis);
}

void ViewQtQuick::Index::setSceneData(osg::NodeQtQml *node)
{
    othis->setSceneData(node->node());
}

osg::CameraQtQml *ViewQtQuick::Index::getCamera()
{
    return osg::CameraQtQml::fromCamera(othis->getCamera(), qthis);
}

void ViewQtQuick::Index::setCamera(osg::CameraQtQml *camera)
{
    othis->setCamera(camera->camera());
}

osgGA::CameraManipulatorQtQml *ViewQtQuick::Index::getCameraManipulator()
{
    return osgGA::CameraManipulatorQtQml::fromCameraManipulator(othis->getCameraManipulator(), qthis);
}

void ViewQtQuick::Index::setCameraManipulator(osgGA::CameraManipulatorQtQml *manipulator)
{
    othis->setCameraManipulator(manipulator->cameraManipulator());
}

void ViewQtQuick::Index::classBegin()
{
    if(!othis) othis = new View();

    qthis->setAcceptHoverEvents(true);
    qthis->setAcceptedMouseButtons(Qt::AllButtons);

    preDraw = new PreDraw(this);
    othis->getCamera()->setPreDrawCallback(preDraw.get());

    postDraw = new PostDraw(this);
    othis->getCamera()->setPostDrawCallback(postDraw.get());

    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

void ViewQtQuick::Index::setKeyboardModifiers(QInputEvent *event)
{
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    unsigned int mask = 0;
    if ( modkey & Qt::ShiftModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    if ( modkey & Qt::ControlModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    if ( modkey & Qt::AltModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
    othis->getEventQueue()->getCurrentEventState()->setModKeyMask( mask );
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
    qreal x = 2.0 * (event->x() - qthis->width() / 2) / qthis->width();
    qreal y = 2.0 * (event->y() - qthis->height() / 2) / qthis->height();

    return QPointF(x, y);
}

void ViewQtQuick::Index::mouseButtonPress(QMouseEvent *event)
{
    int button = mouseButton(event);
    setKeyboardModifiers(event);
    QPointF pos = mousePoint(event);
    othis->getEventQueue()->mouseButtonPress(pos.x(), pos.y(), button);
}

void ViewQtQuick::Index::mouseMotion(QMouseEvent *event)
{
    setKeyboardModifiers(event);
    QPointF pos = mousePoint(event);
    othis->getEventQueue()->mouseMotion(pos.x(), pos.y());
}

void ViewQtQuick::Index::mouseButtonRelease(QMouseEvent *event)
{
    int button = mouseButton(event);
    setKeyboardModifiers(event);
    QPointF pos = mousePoint(event);
    othis->getEventQueue()->mouseButtonRelease(pos.x(), pos.y(), button);
}

void ViewQtQuick::Index::mouseDoubleButtonPress(QMouseEvent *event)
{
    int button = mouseButton(event);
    setKeyboardModifiers(event);
    QPointF pos(event->x(), qthis->height() - event->y());
    othis->getEventQueue()->mouseDoubleButtonPress(pos.x(), pos.y(), button);
}

void ViewQtQuick::Index::initFBO()
{
    QRectF rect = qthis->mapRectToItem(0, qthis->boundingRect());
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    QSize size(rect.size().toSize());
    fbo = new QOpenGLFramebufferObject(size, format);
    texture = qthis->window()->createTextureFromId(fbo->texture(), size);
    textureNode = new QSGSimpleTextureNode();
    textureNode->setRect(0, qthis->height(), qthis->width(), -qthis->height());
    textureNode->setTexture(texture);
    qthis->setFlag(QQuickItem::ItemHasContents, true);
    updateViewport();
    qthis->update();
}

void ViewQtQuick::Index::updateFBO()
{
    if (fbo) delete fbo;
    QRectF rect = qthis->mapRectToItem(0, qthis->boundingRect());
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    QSize size(rect.size().toSize());
    fbo = new QOpenGLFramebufferObject(size, format);
    if (texture) delete texture;
    texture = qthis->window()->createTextureFromId(fbo->texture(), size);
    textureNode = new QSGSimpleTextureNode();
    textureNode->setRect(0, qthis->height(), qthis->width(), -qthis->height());
    textureNode->setTexture(texture);
    qthis->update();
}

void ViewQtQuick::Index::updateViewport()
{
    QSize size(qthis->boundingRect().size().toSize());
    othis->getCamera()->setViewport(0, 0, size.width(), size.height());
    othis->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(size.width())/static_cast<double>(size.height()), 1.0f, 10000.0f );
    if (texture && texture->textureSize() != size) {
        updateFBO();
    }
}

void ViewQtQuick::Index::acceptWindow(osgQtQuick::Window *window)
{
    othis->getCamera()->setGraphicsContext(window->graphicsContext());
    updateViewport();
    window->viewer()->addView(othis);
}

ViewQtQuick *ViewQtQuick::fromView(View *view, QQuickItem *parent)
{
    if(!view) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(view))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new ViewQtQuick(new Index(view), parent);
}

void ViewQtQuick::mousePressEvent(QMouseEvent *event)
{
    static_cast<Index*>(i)->mouseButtonPress(event);
}

void ViewQtQuick::mouseMoveEvent(QMouseEvent *event)
{
    static_cast<Index*>(i)->mouseMotion(event);
}

void ViewQtQuick::mouseReleaseEvent(QMouseEvent *event)
{
    static_cast<Index*>(i)->mouseButtonRelease(event);
}

void ViewQtQuick::mouseDoubleClickEvent(QMouseEvent *event)
{

    static_cast<Index*>(i)->mouseDoubleButtonPress(event);
}

void ViewQtQuick::wheelEvent(QWheelEvent *event)
{
    static_cast<Index*>(i)->othis->getEventQueue()->mouseScroll(
                event->orientation() == Qt::Vertical ?
                    (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
                    (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT) );
}

void ViewQtQuick::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    osgQtQuick::Object::geometryChanged(newGeometry, oldGeometry);

    static_cast<Index*>(i)->updateViewport();
}

QSGNode *ViewQtQuick::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    if (oldNode && oldNode != static_cast<Index*>(i)->textureNode) {
        delete oldNode;
    }
    Q_UNUSED(updatePaintNodeData);

    return static_cast<Index*>(i)->textureNode;
}

void ViewQtQuick::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &value)
{
    if(change == QQuickItem::ItemSceneChange)
    {
        if(osgQtQuick::Window *window =
                osgQtQuick::Window::fromWindow(value.window))
        {
            static_cast<Index*>(i)->acceptWindow(window);
        }
    }
    osgQtQuick::Object::itemChange(change, value);
}

osg::NodeQtQml *ViewQtQuick::getSceneData()
{
    return static_cast<Index*>(i)->getSceneData();
}

void ViewQtQuick::setSceneData(osg::NodeQtQml *node)
{
    static_cast<Index*>(i)->setSceneData(node);
}

osg::CameraQtQml *ViewQtQuick::getCamera()
{
    return static_cast<Index*>(i)->getCamera();
}

void ViewQtQuick::setCamera(osg::CameraQtQml *camera)
{
    static_cast<Index*>(i)->setCamera(camera);
}


osgGA::CameraManipulatorQtQml *ViewQtQuick::getCameraManipulator()
{
    return static_cast<Index*>(i)->getCameraManipulator();
}

void ViewQtQuick::setCameraManipulator(osgGA::CameraManipulatorQtQml *manipulator)
{
    static_cast<Index*>(i)->setCameraManipulator(manipulator);
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQuick::Object::classBegin();
}

void ViewQtQuick::componentComplete()
{
    osgQtQuick::Object::componentComplete();
}

}
