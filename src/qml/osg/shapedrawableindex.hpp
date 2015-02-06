#ifndef _OSG_SHAPEDRAWABLE_QTQML_INDEX_
#define _OSG_SHAPEDRAWABLE_QTQML_INDEX_ 1

#include <osg/ShapeDrawableQtQml>

#include <osg/DrawableQtQmlIndex>

#include <osg/Shape>

namespace osg {

class OSGQTQML_EXPORT ShapeDrawableQtQml::Index : public DrawableQtQml::Index
{
    friend class ShapeDrawableQtQml;

public:
    Index(ShapeDrawable *o = 0);

    void classBegin();
    void componentComplete();

    ShapeQtQml *getShape() const;
    void setShape(ShapeQtQml *shape);

protected:
    ShapeDrawable *othis;
    ShapeDrawableQtQml *qthis;

    osg::ref_ptr<Shape> shape;
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_INDEX_
