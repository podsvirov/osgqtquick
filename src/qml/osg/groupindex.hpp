#ifndef _OSG_GROUP_QTQML_INDEX_
#define _OSG_GROUP_QTQML_INDEX_ 1

#include <osg/GroupQtQml>

#include <osg/NodeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT GroupQtQml::Index : public NodeQtQml::Index
{
    friend class GroupQtQml;

public:
    Index(Group *o = 0);

    void classBegin();

    bool addChild(NodeQtQml *child);
    bool removeChild(NodeQtQml *child);

protected:
    Group *othis;
    GroupQtQml *qthis;
};

}

#endif // _OSG_GROUP_QTQML_INDEX_
