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
    OrbitManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void NodeTrackerManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new NodeTrackerManipulator();
    OrbitManipulatorQtQml::Index::othis = othis;
    OrbitManipulatorQtQml::Index::qthis = qthis;

    OrbitManipulatorQtQml::Index::classBegin();
}

void NodeTrackerManipulatorQtQml::Index::setTrackNode(osg::NodeQtQml *node)
{
  osg::Node *a = node->node();

  if(othis->getTrackNode() == a) return;

  othis->setTrackNode(a);

  emit qthis->trackNodeChanged(node);
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    OrbitManipulatorQtQml::classBegin();
}

/*!
   \qmlproperty osg::Node osgGA::NodeTrackerManipulator::trackNode

   Tracked \l {osg::Node}{node}.
 */

osg::NodeQtQml *NodeTrackerManipulatorQtQml::getTrackNode()
{
    return osg::NodeQtQml::fromNode(static_cast<Index*>(i)->othis->getTrackNode(), this);
}

void NodeTrackerManipulatorQtQml::setTrackNode(osg::NodeQtQml *node)
{
    static_cast<Index*>(i)->setTrackNode(node);
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
    return static_cast<TrackerMode>(static_cast<Index*>(i)->othis->getTrackerMode());
}

void NodeTrackerManipulatorQtQml::setTrackerMode(NodeTrackerManipulatorQtQml::TrackerMode mode)
{
    NodeTrackerManipulator::TrackerMode a =
            static_cast<NodeTrackerManipulator::TrackerMode>(mode);

    if(static_cast<Index*>(i)->othis->getTrackerMode() == a) return;

    static_cast<Index*>(i)->othis->setTrackerMode(a);

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
    return static_cast<RotationMode>(static_cast<Index*>(i)->othis->getRotationMode());
}

void NodeTrackerManipulatorQtQml::setRotationMode(NodeTrackerManipulatorQtQml::RotationMode mode)
{
    NodeTrackerManipulator::RotationMode a =
            static_cast<NodeTrackerManipulator::RotationMode>(mode);

    if(static_cast<Index*>(i)->othis->getRotationMode() == a) return;

    static_cast<Index*>(i)->othis->setRotationMode(a);

    emit rotationModeChanged(mode);
}

NodeTrackerManipulator *NodeTrackerManipulatorQtQml::nodeTrackerManipulator()
{
    return static_cast<Index*>(i)->othis;
}

NodeTrackerManipulatorQtQml *NodeTrackerManipulatorQtQml::fromNodeTrackerManipulator(NodeTrackerManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new NodeTrackerManipulatorQtQml(new Index(trackballManipulator), parent);
}

}
