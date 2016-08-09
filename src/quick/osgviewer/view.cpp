#include "view.hpp"
#include "viewindex.hpp"

#include "../renderthread.hpp"

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
    //if (!i->renderFbo) i->initFBO();
    //i->needUpdateFboMutex.lock();
    if(i->needUpdate)
    {
        i->prepareObject();
        --i->needUpdate;
    }
    //i->needUpdateFboMutex.unlock();
//    if (i->renderFbo->size() != i->size) {
//        {
//            qDebug() << i->renderFbo->size() << "!=" << i->size;
////            i->needUpdateFboMutex.lock();
////            bool need = i->needUpdateFbo;
////            i->needUpdateFboMutex.unlock();
////            if(need)
//                i->updateFBO();
//        }
//    }
    i->renderFbo->bind();
}

/* ------------------------------------------------------ struct PostDraw --- */

ViewQtQuick::Index::PostDraw::PostDraw(Index *i) : i(i) {
}

void ViewQtQuick::Index::PostDraw::operator ()(osg::RenderInfo &/*renderInfo*/) const
{
    if (i->renderFbo) {
        if(i->window->renderLoopType() == osgQtQuick::ThreadedRenderLoop) {
            i->window->renderThread()->context->functions()->glFlush();
            i->renderFbo->bindDefault();
            qSwap(i->renderFbo, i->displayFbo);
            qSwap(i->renderTexture, i->displayTexture);
        } else {
            i->renderFbo->bindDefault();
        }
    }
}

/* ---------------------------------------------------------- class Index --- */

ViewQtQuick::Index::Index(View *view) :
    osgQtQuick::Index(view)
{
    window = 0;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    renderFbo = 0;
    displayFbo = 0;
    renderTexture = 0;
    needUpdate = 4;
    displayTexture = 0;
    textureNode = 0;
}

ViewQtQuick::Index::~Index()
{
    if(window) {
        window->removeView(this);
        window = 0;
    }
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

void ViewQtQuick::Index::prepareNode()
{
    if(!displayFbo)
        return;

    //needUpdateFboMutex.lock();
    if(needUpdate) {
        qDebug() << "[osgQtQuick] updateTexture" << needUpdate;
        if(displayTexture)
            delete displayTexture;
        displayTexture = window->quickWindow()->createTextureFromId(displayFbo->texture(), size);
        if(!textureNode) {
            qDebug() << "[osgQtQuick] Create texture node for" << q(this);
            textureNode = new QSGSimpleTextureNode();
            QMetaObject::invokeMethod(q(this), "update", Qt::QueuedConnection);
        }
        textureNode->setRect(0, q(this)->height(), q(this)->width(), -q(this)->height());
        --needUpdate;
    }
    //needUpdateFboMutex.unlock();

//    if(!displayTexture) {

//        qDebug() << "[osgQtQuick] Create new texture for" << q(this);
//        displayTexture = window->quickWindow()->createTextureFromId(displayFbo->texture(), size);
//        textureNode->setRect(0, q(this)->height(), q(this)->width(), -q(this)->height());
//    }

    textureNode->setTexture(displayTexture);
}

void ViewQtQuick::Index::classBegin()
{
    if(!o(this)) setO(new View);

    q(this)->setAcceptHoverEvents(true);
    q(this)->setAcceptedMouseButtons(Qt::AllButtons);

    //textureNode = new QSGSimpleTextureNode();

    osgGA::GUIEventAdapter *ea = o(this)->getEventQueue()->getCurrentEventState();
    ea->setMouseYOrientation(osgGA::GUIEventAdapter::Y_INCREASING_UPWARDS);

    context = new osgViewer::GraphicsWindowEmbedded(0, 0, 1, 1);

    preDraw = new PreDraw(this);
    o(this)->getCamera()->setPreDrawCallback(preDraw.get());

    postDraw = new PostDraw(this);
    o(this)->getCamera()->setPostDrawCallback(postDraw.get());

    osgQtQuick::Index::classBegin();
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
    qreal x = event->x();
    qreal y = q(this)->height() - event->y();

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
    qDebug() << "[osgQtQuick] initFBO for" << q(this);

    //QRectF rect = q(this)->mapRectToItem(0, q(this)->boundingRect());
    //size = rect.size().toSize();
    //size = q(this)->boundingRect().size().toSize();
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

    renderFbo = new QOpenGLFramebufferObject(size, format);
    textureNode = new QSGSimpleTextureNode();
    //qDebug() << "[osgQtQuick] renderFbo->texture()" << renderFbo->texture();
    if(window->renderLoopType() == osgQtQuick::ThreadedRenderLoop) {
        displayFbo = new QOpenGLFramebufferObject(size, format);
        //displayTexture = q(this)->window()->createTextureFromId(displayFbo->texture(), size);
        //qDebug() << "[osgQtQuick] displayFbo->texture()" << displayFbo->texture();
    } else {
        renderTexture = q(this)->window()->createTextureFromId(renderFbo->texture(), size);
        //textureNode = new QSGSimpleTextureNode();
        textureNode->setRect(0, q(this)->height(), q(this)->width(), -q(this)->height());
        textureNode->setTexture(renderTexture);
        q(this)->setFlag(QQuickItem::ItemHasContents, true);

        displayFbo = renderFbo;
        displayTexture = renderTexture;
    }
    updateViewport();
    QMetaObject::invokeMethod(q(this), "update", Qt::QueuedConnection);
}

void ViewQtQuick::Index::updateFBO()
{
    qDebug() << "[osgQtQuick] updateFBO";
    if (renderFbo) {
        delete renderFbo;
        renderFbo = 0;
    }
//    if (renderTexture) {
//        delete renderTexture;
//        renderTexture = 0;
//    }
    //QRectF rect = q(this)->mapRectToItem(0, q(this)->boundingRect());
    //size = rect.size().toSize();
    //size = q(this)->boundingRect().size().toSize();
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    renderFbo = new QOpenGLFramebufferObject(size, format);
    if(window->renderLoopType() == osgQtQuick::ThreadedRenderLoop)
    {
        if (displayFbo) {
            delete displayFbo;
            displayFbo = 0;
        }
//        if (displayTexture) {
//            delete displayTexture;
//            displayTexture = 0;
//        }
        displayFbo = new QOpenGLFramebufferObject(size, format);
        //displayTexture = q(this)->window()->createTextureFromId(displayFbo->texture(), size);
    } else {
        renderTexture = q(this)->window()->createTextureFromId(renderFbo->texture(), size);
        //textureNode = new QSGSimpleTextureNode();
        textureNode->setRect(0, q(this)->height(), q(this)->width(), -q(this)->height());
        textureNode->setTexture(renderTexture);
    }
    QMetaObject::invokeMethod(q(this), "update", Qt::QueuedConnection);
}

void ViewQtQuick::Index::prepareObject()
{
    qDebug() << "[osgQtQuick] updateFbo" << needUpdate << size;
    if(renderFbo)
        delete renderFbo;
    renderFbo = new QOpenGLFramebufferObject(size, format);

//    if(!textureNode) {
//        qDebug() << "[osgQtQuick] Create texture node for" << q(this);
//        textureNode = new QSGSimpleTextureNode();
//        QMetaObject::invokeMethod(q(this), "update", Qt::QueuedConnection);
//    }
}

void ViewQtQuick::Index::updateViewport()
{
    //QRectF rect = q(this)->mapRectToItem(0, q(this)->boundingRect());
    //size = rect.size().toSize();
    size = q(this)->boundingRect().size().toSize();
    context->resizedImplementation(0, 0, size.width(), size.height());
    osgGA::GUIEventAdapter *ea = o(this)->getEventQueue()->getCurrentEventState();
    ea->setXmin(0);
    ea->setXmax(size.width());
    ea->setYmin(0);
    ea->setYmax(size.height());
    o(this)->getCamera()->setViewport(0, 0, size.width(), size.height());
    o(this)->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(size.width())/static_cast<double>(size.height()), 1.0f, 10000.0f );
    //if (displayTexture && displayTexture->textureSize() != size) {
    if (textureNode) {
        if(window->renderLoopType() == osgQtQuick::ThreadedRenderLoop) {
            //needUpdateFboMutex.lock();
            //qDebug() << "needUpdate % 4 =" << (needUpdate % 4);
            needUpdate = needUpdate % 4 + 4;
            //needUpdateFboMutex.unlock();
        } else {
            updateFBO();
        }
    }
}

void ViewQtQuick::Index::acceptWindow(osgQtQuick::Window *window)
{
    if(this->window) {
        // TODO: Clear window dependencies
    }

    this->window = window;

    qDebug() << "[osgQtQuick] ViewQtQuick::Index::acceptWindow";
    o(this)->getCamera()->setGraphicsContext(context);
    o(this)->getEventQueue()->setGraphicsContext(context);
    updateViewport();

    window->addView(this);

    if(window->renderLoopType() == osgQtQuick::ThreadedRenderLoop)
    {
        q(this)->setFlag(ItemHasContents, true);
    }
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
    qDebug() << "[osgQtQuick] View geomerty changed from" << oldGeometry << "to" << newGeometry;

    i(this)->size = boundingRect().size().toSize();

    if(i(this)->window) {
        i(this)->updateViewport();
    } else {
        qDebug() << "No Window!!!";
    }

    osgQtQuick::Object::geometryChanged(newGeometry, oldGeometry);
}

QSGNode *ViewQtQuick::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    qDebug() << "[osgQtQuick] updatePaintNode for" << this;

    if (oldNode && oldNode != i(this)->textureNode) {
        qDebug() << "[osgQtQuick] ViewQtQuick::updatePaintNode delete old node" << oldNode;
        delete oldNode;
    }
    Q_UNUSED(updatePaintNodeData);

    // Delay context initialization
    osgQtQuick::RenderThread *renderThread = i(this)->window->renderThread();
    if (renderThread && !renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        current->doneCurrent();

        renderThread->context = new QOpenGLContext();
        renderThread->context->setFormat(current->format());
        renderThread->context->setShareContext(current);
        renderThread->context->create();
        renderThread->context->moveToThread(renderThread);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(i(this)->window, "ready");
        return 0;
    }

    i(this)->size = boundingRect().size().toSize();

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
    qDebug() << "[osgQtQuick] New ViewQtQuick";
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

}
