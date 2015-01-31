#ifndef _OSG_TRANSFORM_QTQML_INDEX_
#define _OSG_TRANSFORM_QTQML_INDEX_ 1

#include <osg/TransformQtQml>

#include <osg/GroupQtQmlIndex>

namespace osg {

class Transform;

class OSGQTQML_EXPORT TransformQtQml::Index : public GroupQtQml::Index
{
    friend class TransformQtQml;

public:
    Index(Transform *o = 0);

    void classBegin();

    bool addChild(NodeQtQml *child);
    bool removeChild(NodeQtQml *child);

protected:
    Transform *othis;
    TransformQtQml *qthis;
};

}

#endif // _OSG_TRANSFORM_QTQML_INDEX_
