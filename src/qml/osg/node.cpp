#include "node.hpp"
#include "nodeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Node>

namespace osg {

/*!
   \qmltype Node
   \inherits Object
   \inqmlmodule osg
   \brief Base type for all internal nodes in the scene graph
 */

NodeQtQml::Index::Index(Node *node) :
    ObjectQtQml::Index(node)
{
}

void NodeQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Node);

    ObjectQtQml::Index::classBegin();
}

NodeQtQml::NodeQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

NodeQtQml::NodeQtQml(NodeQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void NodeQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ObjectQtQml::classBegin();
}

Node *NodeQtQml::node()
{
    return o(this);
}

NodeQtQml *NodeQtQml::fromNode(Node *node, QObject *parent)
{
    if(!node) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(node))
    {
        return static_cast<NodeQtQml*>(index->qtObject());
    }

    NodeQtQml *result = new NodeQtQml(new Index(node), parent);
    result->classBegin();

    return result;
}

}
