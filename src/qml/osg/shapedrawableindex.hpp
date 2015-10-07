#ifndef _OSG_SHAPEDRAWABLE_QTQML_INDEX_
#define _OSG_SHAPEDRAWABLE_QTQML_INDEX_ 1

#include <osg/ShapeDrawableQtQml>

#include <osg/DrawableQtQmlIndex>

#include <osg/Shape>

namespace osg {

class OSGQTQML_EXPORT ShapeDrawableQtQml::Index : public DrawableQtQml::Index
{
public:
    typedef ShapeDrawable OType;
    typedef ShapeDrawableQtQml QType;
    friend class ShapeDrawableQtQml;

public:
    Index(ShapeDrawable *o = 0);

    void componentComplete();

    ShapeQtQml *getShape() const;
    void setShape(ShapeQtQml *shape);

    void setColor(const QColor &color);

protected:
    osg::ref_ptr<Shape> shape;
    QColor color;
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_INDEX_
