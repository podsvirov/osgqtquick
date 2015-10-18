#include "nodetrackermanipulator.hpp"
#include "nodetrackermanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/NodeTrackerManipulator>

#include <QDebug>

/*!
   \qmltype NodeTrackerManipulator
   \inherits OrbitManipulator
   \inqmlmodule osgGA
   \brief Control based on tracked node position and orientation
 */

namespace osgGA {

NodeTrackerManipulatorQtQml::Index::Index(NodeTrackerManipulator *manipulator) :
    OrbitManipulatorQtQml::Index(manipulator)
{
}

void NodeTrackerManipulatorQtQml::Index::classBegin()
{
    if(!o(this)) setO(new NodeTrackerManipulator);

    OrbitManipulatorQtQml::Index::classBegin();
}

void NodeTrackerManipulatorQtQml::Index::setTrackNode(osg::NodeQtQml *node)
{
  osg::Node *a = node->node();

  if(o(this)->getTrackNode() == a) return;

  o(this)->setTrackNode(a);

  emit q(this)->trackNodeChanged(node);
}

NodeTrackerManipulatorQtQml::NodeTrackerManipulatorQtQml(QObject *parent) :
  OrbitManipulatorQtQml(parent)
{
}

NodeTrackerManipulatorQtQml::NodeTrackerManipulatorQtQml(NodeTrackerManipulatorQtQml::Index *index, QObject *parent) :
  OrbitManipulatorQtQml(index, parent)
{
}

void NodeTrackerManipulatorQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    OrbitManipulatorQtQml::classBegin();
}

/*!
   \qmlproperty osg::Node osgGA::NodeTrackerManipulator::trackNode

   Tracked \l {osg::Node}{node}.
 */

osg::NodeQtQml *NodeTrackerManipulatorQtQml::getTrackNode()
{
    return osg::NodeQtQml::fromNode(o(this)->getTrackNode(), this);
}

void NodeTrackerManipulatorQtQml::setTrackNode(osg::NodeQtQml *node)
{
    i(this)->setTrackNode(node);
}

/*!
   \qmlproperty enumeration osgGA::NodeTrackerManipulator::trackerMode

   Tracker mode. It can be one of:
   \list
   \li NodeTrackerManipulator.NODE_CENTER - Track the center of the node's bounding sphere,
       but not rotations of the node.
   \li NodeTrackerManipulator.NODE_CENTER_AND_AZIM - Track the center of the node's bounding sphere,
       and the azimuth rotation (about the z axis of the current coordinate frame).
   \li NodeTrackerManipulator.NODE_CENTER_AND_ROTATION - Tack the center of the node's bounding sphere, and the all rotations of the node.
   \endlist
 */

NodeTrackerManipulatorQtQml::TrackerMode NodeTrackerManipulatorQtQml::getTrackerMode()
{
    return static_cast<TrackerMode>(o(this)->getTrackerMode());
}

void NodeTrackerManipulatorQtQml::setTrackerMode(NodeTrackerManipulatorQtQml::TrackerMode mode)
{
    NodeTrackerManipulator::TrackerMode a =
            static_cast<NodeTrackerManipulator::TrackerMode>(mode);

    if(o(this)->getTrackerMode() == a) return;

    o(this)->setTrackerMode(a);

    emit trackerModeChanged(mode);
}

/*!
   \qmlproperty enumeration osgGA::NodeTrackerManipulator::rotationMode

   Rotation mode. It can be one of:
   \list
   \li NodeTrackerManipulator.TRACKBALL - Use a trackball style manipulation of the view direction w.r.t the tracked orientation.
   \li NodeTrackerManipulator.ELEVATION_AZIM - Allow the elevation and azimuth angles to be adjust w.r.t the tracked orientation.
   \endlist
 */

NodeTrackerManipulatorQtQml::RotationMode NodeTrackerManipulatorQtQml::getRotationMode()
{
    return static_cast<RotationMode>(o(this)->getRotationMode());
}

void NodeTrackerManipulatorQtQml::setRotationMode(NodeTrackerManipulatorQtQml::RotationMode mode)
{
    NodeTrackerManipulator::RotationMode a =
            static_cast<NodeTrackerManipulator::RotationMode>(mode);

    if(o(this)->getRotationMode() == a) return;

    o(this)->setRotationMode(a);

    emit rotationModeChanged(mode);
}

NodeTrackerManipulator *NodeTrackerManipulatorQtQml::nodeTrackerManipulator()
{
    return o(this);
}

NodeTrackerManipulatorQtQml *NodeTrackerManipulatorQtQml::fromNodeTrackerManipulator(NodeTrackerManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<NodeTrackerManipulatorQtQml*>(index->qtObject());
    }

    NodeTrackerManipulatorQtQml *result = new NodeTrackerManipulatorQtQml(new Index(trackballManipulator), parent);
    result->classBegin();
    return result;
}

}
