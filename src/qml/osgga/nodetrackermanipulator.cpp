#include "nodetrackermanipulator.hpp"
#include "nodetrackermanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/NodeTrackerManipulator>

#include <QDebug>

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

osg::NodeQtQml *NodeTrackerManipulatorQtQml::getTrackNode()
{
    return osg::NodeQtQml::fromNode(static_cast<Index*>(i)->othis->getTrackNode(), this);
}

void NodeTrackerManipulatorQtQml::setTrackNode(osg::NodeQtQml *node)
{
    static_cast<Index*>(i)->setTrackNode(node);
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
