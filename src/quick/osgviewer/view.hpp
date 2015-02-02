#ifndef _OSGVIEWER_VIEW_QTQUICK_
#define _OSGVIEWER_VIEW_QTQUICK_ 1

#include <osgQtQuick/Object>

#include <osg/NodeQtQml>

namespace osgViewer {

class View;

class OSGQTQUICK_EXPORT ViewQtQuick : public osgQtQuick::Object
{
  Q_OBJECT

  Q_PROPERTY(osg::NodeQtQml* sceneData READ getSceneData WRITE setSceneData NOTIFY sceneDataChanged)

public:
  class Index;

  Q_INVOKABLE osg::NodeQtQml* getSceneData();
  Q_INVOKABLE void setSceneData(osg::NodeQtQml *node);

  ViewQtQuick(QQuickItem *parent = 0);
  ViewQtQuick(Index *index, QQuickItem *parent = 0);

  void classBegin();
  void componentComplete();

  static ViewQtQuick* fromView(View *view, QQuickItem *parent = 0);

signals:
  void sceneDataChanged(osg::NodeQtQml *node);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  void	geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);

  QSGNode* updatePaintNode(QSGNode *oldNode,
                           QQuickItem::UpdatePaintNodeData *updatePaintNodeData);

  void itemChange(ItemChange change, const ItemChangeData & value);
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_
