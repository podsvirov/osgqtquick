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
    ~Index();

    void classBegin();

protected:
    Group *othis;
    GroupQtQml *qthis;

    struct CompleteInfo;
    CompleteInfo *_completeInfo;

    CompleteInfo* info();
};

struct GroupQtQml::Index::CompleteInfo
{
  QList<NodeQtQml*> child;
};

inline GroupQtQml::Index::CompleteInfo *GroupQtQml::Index::info()
{
  return _completeInfo ? _completeInfo : _completeInfo = new CompleteInfo;
}

}

#endif // _OSG_GROUP_QTQML_INDEX_
