#ifndef _OSG_GROUP_QTQML_INDEX_
#define _OSG_GROUP_QTQML_INDEX_ 1

#include <osg/GroupQtQml>

#include <osg/NodeQtQmlIndex>

namespace osg {

class Group;

class OSGQTQML_EXPORT GroupQtQml::Index : public NodeQtQml::Index
{
public:
    Index(Group *o = 0);

    bool addChild(NodeQtQml *child);
    bool removeChild(NodeQtQml *child);
};

}

#endif // _OSG_GROUP_QTQML_INDEX_
