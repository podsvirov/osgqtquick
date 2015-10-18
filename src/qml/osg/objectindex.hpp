#ifndef _OSG_OBJECT_QTQML_INDEX_
#define _OSG_OBJECT_QTQML_INDEX_ 1

#include <osgQtQml/Index>

#include <osg/ObjectQtQml>

namespace osg {

class OSGQTQML_EXPORT ObjectQtQml::Index : public osgQtQml::Index
{
public:
    typedef osg::Object OType;
    typedef ObjectQtQml QType;
    friend class ObjectQtQml;

public:
    Index(osg::Object *object = 0);
};

}

#endif // _OSG_OBJECT_QTQML_INDEX_
