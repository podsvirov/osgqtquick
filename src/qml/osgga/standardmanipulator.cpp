#include "standardmanipulator.hpp"
#include "standardmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/StandardManipulator>

#include <QDebug>

/*!
   \qmltype StandardManipulator
   \inherits CameraManipulator
   \inqmlmodule osgGA
   \brief Provides basic functionality for user controlled manipulation
 */

namespace osgGA {

StandardManipulatorQtQml::Index::Index(StandardManipulator *manipulator) :
    CameraManipulatorQtQml::Index(manipulator)
{
}

void StandardManipulatorQtQml::Index::setNode(osg::NodeQtQml *node)
{
    osg::Node *a = node->node();

    if(o(this)->getNode() == a) return;

    o(this)->setNode(a);

    emit q(this)->nodeChanged(node);
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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    CameraManipulatorQtQml::classBegin();
}

/*!
   \qmlproperty osg::Node osgGA::StandardManipulator::node

   Attached \l {osg::Node}{node}.
 */

osg::NodeQtQml *StandardManipulatorQtQml::getNode()
{
    return osg::NodeQtQml::fromNode(o(this)->getNode(), this);
}

void StandardManipulatorQtQml::setNode(osg::NodeQtQml *node)
{
    i(this)->setNode(node);
}

StandardManipulator *StandardManipulatorQtQml::standardManipulator()
{
    return o(this);
}

StandardManipulatorQtQml *StandardManipulatorQtQml::fromStandardManipulator(StandardManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<StandardManipulatorQtQml*>(index->qtObject());
    }

    return new StandardManipulatorQtQml(new Index(trackballManipulator), parent);
}

}
