#include "node.hpp"
#include "nodeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Node>

namespace osg {

NodeQtQml::Index::Index(Node *o) :
    osgQtQml::Index(o ? o : new osg::Node())
{
}

NodeQtQml::NodeQtQml(QObject *parent) :
  Object(new osgQtQml::Index(new osg::Node()), parent)
  //Object(parent)
{
    //i = new Index(new osg::Node(), this);
}

NodeQtQml::NodeQtQml(NodeQtQml::Index *index, QObject *parent) :
  Object(index, parent)
{

}

}
