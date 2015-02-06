#ifndef _OSG_SHAPE_QTQML_INDEX_
#define _OSG_SHAPE_QTQML_INDEX_ 1

#include <osg/ShapeQtQml>

#include <osg/ObjectQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT ShapeQtQml::Index : public ObjectQtQml::Index
{
    friend class ShapeQtQml;

public:
    Index(Shape *o = 0);
    void classBegin();

protected:
    Shape *othis;
    ShapeQtQml *qthis;
};

}

#endif // _OSG_SHAPE_QTQML_INDEX_
