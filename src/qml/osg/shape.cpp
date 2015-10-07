#include "shape.hpp"
#include "shapeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

/*!
   \qmltype Shape
   \inherits Object
   \inqmlmodule osg
   \brief Base type for all shape types
 */

namespace osg {

ShapeQtQml::Index::Index(Shape *shape) :
    ObjectQtQml::Index(shape)
{
}

ShapeQtQml::ShapeQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

ShapeQtQml::ShapeQtQml(ShapeQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void ShapeQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

Shape *ShapeQtQml::shape()
{
    return o(this);
}

ShapeQtQml *ShapeQtQml::fromShape(Shape *shape, QObject *parent)
{
    if(!shape) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(shape))
    {
        return static_cast<ShapeQtQml*>(index->qtObject());
    }

    ShapeQtQml *result = new ShapeQtQml(new Index(shape), parent);
    result->classBegin();
    return result;
}

}
