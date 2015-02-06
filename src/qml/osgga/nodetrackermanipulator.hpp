#ifndef _OSGGA_NODETRACKERMANIPULATOR_QTQML_
#define _OSGGA_NODETRACKERMANIPULATOR_QTQML_ 1

#include <osgGA/OrbitManipulatorQtQml>

#include <osg/NodeQtQml>

namespace osgGA {

class NodeTrackerManipulator;

class OSGQTQML_EXPORT NodeTrackerManipulatorQtQml : public OrbitManipulatorQtQml
{
  Q_OBJECT

  Q_PROPERTY(osg::NodeQtQml* trackNode READ getTrackNode WRITE setTrackNode NOTIFY trackNodeChanged)

public:
  class Index;

  NodeTrackerManipulatorQtQml(QObject *parent = 0);
  NodeTrackerManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE osg::NodeQtQml *getTrackNode();
  Q_INVOKABLE void setTrackNode(osg::NodeQtQml *node);

  NodeTrackerManipulator* nodeTrackerManipulator();

  static NodeTrackerManipulatorQtQml* fromNodeTrackerManipulator(NodeTrackerManipulator *manipulator, QObject *parent = 0);

signals:
  void trackNodeChanged(osg::NodeQtQml *node);
};

}

#endif // _OSGGA_NODETRACKERMANIPULATOR_QTQML_
