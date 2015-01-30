#ifndef _OSG_NODE_QTQML_INDEX_
#define _OSG_NODE_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/NodeQtQml>

namespace osg {

class OSGQTQML_EXPORT NodeQtQml::Index : public ObjectQtQml::Index
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
