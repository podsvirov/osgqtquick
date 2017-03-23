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
  Q_PROPERTY(TrackerMode trackerMode READ getTrackerMode WRITE setTrackerMode NOTIFY trackerModeChanged)
  Q_PROPERTY(RotationMode rotationMode READ getRotationMode WRITE setRotationMode NOTIFY rotationModeChanged)

  Q_ENUMS(TrackerMode)
  Q_ENUMS(RotationMode)

public:
  class Index;

  enum TrackerMode {
      NODE_CENTER,
      NODE_CENTER_AND_AZIM,
      NODE_CENTER_AND_ROTATION
  };

  enum RotationMode {
      TRACKBALL,
      ELEVATION_AZIM
  };

  NodeTrackerManipulatorQtQml(QObject *parent = 0);
  NodeTrackerManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE osg::NodeQtQml *getTrackNode();
  Q_INVOKABLE void setTrackNode(osg::NodeQtQml *node);

  Q_INVOKABLE TrackerMode getTrackerMode();
  Q_INVOKABLE void setTrackerMode(TrackerMode mode);

  Q_INVOKABLE RotationMode getRotationMode();
  Q_INVOKABLE void setRotationMode(RotationMode mode);

  NodeTrackerManipulator* nodeTrackerManipulator();

  static NodeTrackerManipulatorQtQml* fromNodeTrackerManipulator(NodeTrackerManipulator *manipulator, QObject *parent = 0);

Q_SIGNALS:
  void trackNodeChanged(osg::NodeQtQml *node);
  void trackerModeChanged(TrackerMode mode);
  void rotationModeChanged(RotationMode mode);
};

}

#endif // _OSGGA_NODETRACKERMANIPULATOR_QTQML_
