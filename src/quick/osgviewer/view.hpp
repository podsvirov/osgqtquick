#ifndef _OSGVIEWER_VIEW_QTQUICK_
#define _OSGVIEWER_VIEW_QTQUICK_ 1

#include <osgQtQuick/Object>

#include <osg/CameraQtQml>
#include <osgGA/CameraManipulatorQtQml>

namespace osgViewer {

class View;

class OSGQTQUICK_EXPORT ViewQtQuick : public osgQtQuick::Object
{
  Q_OBJECT

  Q_PROPERTY(osg::NodeQtQml* sceneData READ getSceneData WRITE setSceneData NOTIFY sceneDataChanged)
  Q_PROPERTY(osg::CameraQtQml* camera READ getCamera WRITE setCamera NOTIFY cameraChanged)
  Q_PROPERTY(osgGA::CameraManipulatorQtQml* cameraManipulator READ getCameraManipulator WRITE setCameraManipulator NOTIFY cameraManipulatorChanged)

public:
  class Index;

  Q_INVOKABLE osg::NodeQtQml* getSceneData();
  Q_INVOKABLE void setSceneData(osg::NodeQtQml *node);

  Q_INVOKABLE osg::CameraQtQml* getCamera();
  Q_INVOKABLE void setCamera(osg::CameraQtQml *camera);

  Q_INVOKABLE osgGA::CameraManipulatorQtQml* getCameraManipulator();
  Q_INVOKABLE void setCameraManipulator(osgGA::CameraManipulatorQtQml *manipulator);

  ViewQtQuick(QQuickItem *parent = 0);
  ViewQtQuick(Index *index, QQuickItem *parent = 0);

  void classBegin();

  static ViewQtQuick* fromView(View *view, QQuickItem *parent = 0);

Q_SIGNALS:
  void sceneDataChanged(osg::NodeQtQml *node);
  void cameraChanged(osg::CameraQtQml *camera);
  void cameraManipulatorChanged(osgGA::CameraManipulatorQtQml *manipulator);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

  void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);

  QSGNode* updatePaintNode(QSGNode *oldNode,
                           QQuickItem::UpdatePaintNodeData *updatePaintNodeData);

  void itemChange(ItemChange change, const ItemChangeData & value);
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_
