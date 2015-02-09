#include "standardmanipulator.hpp"
#include "standardmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/StandardManipulator>

#include <QDebug>

namespace osgGA {

StandardManipulatorQtQml::Index::Index(StandardManipulator *manipulator) :
    CameraManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void StandardManipulatorQtQml::Index::classBegin()
{
    CameraManipulatorQtQml::Index::othis = othis;
    CameraManipulatorQtQml::Index::qthis = qthis;

    CameraManipulatorQtQml::Index::classBegin();
}

void StandardManipulatorQtQml::Index::setNode(osg::NodeQtQml *node)
{
    osg::Node *a = node->node();

    if(othis->getNode() == a) return;

    othis->setNode(a);

    emit qthis->nodeChanged(node);
}

StandardManipulatorQtQml::StandardManipulatorQtQml(QObject *parent) :
  CameraManipulatorQtQml(parent)
{
}

StandardManipulatorQtQml::StandardManipulatorQtQml(StandardManipulatorQtQml::Index *index, QObject *parent) :
  CameraManipulatorQtQml(index, parent)
{
}

void StandardManipulatorQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    CameraManipulatorQtQml::classBegin();
}

osg::NodeQtQml *StandardManipulatorQtQml::getNode()
{
    return osg::NodeQtQml::fromNode(static_cast<Index*>(i)->othis->getNode(), this);
}

void StandardManipulatorQtQml::setNode(osg::NodeQtQml *node)
{
    static_cast<Index*>(i)->setNode(node);
}

StandardManipulator *StandardManipulatorQtQml::standardManipulator()
{
    return static_cast<Index*>(i)->othis;
}

StandardManipulatorQtQml *StandardManipulatorQtQml::fromStandardManipulator(StandardManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new StandardManipulatorQtQml(new Index(trackballManipulator), parent);
}

}
