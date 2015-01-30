#ifndef _OSGVIEWER_VIEW_QTQUICK_
#define _OSGVIEWER_VIEW_QTQUICK_ 1

#include <osgQtQuick/Object>

#include <osg/NodeQtQml>

namespace osgViewer {

class OSGQTQUICK_EXPORT ViewQtQuick : public osgQtQuick::Object
{
  Q_OBJECT

  Q_PROPERTY(osg::NodeQtQml* sceneData READ getSceneData NOTIFY sceneDataChanged)

public:
  class Index;

  Q_INVOKABLE osg::NodeQtQml* getSceneData();
  Q_INVOKABLE void setSeceneData(osg::NodeQtQml *node);

  ViewQtQuick(QQuickItem *parent = 0);
  ViewQtQuick(Index *index, QQuickItem *parent = 0);

signals:
  void sceneDataChanged(osg::NodeQtQml *node);
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_
