#ifndef _OSG_NODE_QTQML_INDEX_
#define _OSG_NODE_QTQML_INDEX_ 1

#include <osgQtQml/Index>

#include <osg/NodeQtQml>

namespace osg {

class Node;

class OSGQTQML_EXPORT NodeQtQml::Index : public osgQtQml::Index
{
    friend class NodeQtQml;

public:
    Index(Node *o = 0);
    void classBegin();

protected:
    Node *othis;
    NodeQtQml *qthis;
};

}

#endif // _OSG_NODE_QTQML_INDEX_
