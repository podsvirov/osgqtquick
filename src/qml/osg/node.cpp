#include "node.hpp"
#include "nodeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Node>

namespace osg {

NodeQtQml::Index::Index(Node *node) :
    osgQtQml::Index(node),
    qthis(0)
{
    othis = node;
}

void NodeQtQml::Index::classBegin()
{
    if(!othis) othis = new Node();
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

NodeQtQml::NodeQtQml(QObject *parent) :
  Object(parent)
{
}

NodeQtQml::NodeQtQml(NodeQtQml::Index *index, QObject *parent) :
  Object(index, parent)
{
}

void NodeQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

Node *NodeQtQml::node()
{
    return static_cast<Index*>(i)->othis;
}

NodeQtQml *NodeQtQml::fromNode(Node *node, QObject *parent)
{
    if(!node) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(node))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new NodeQtQml(new Index(node), parent);
}

}
