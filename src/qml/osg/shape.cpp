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
    ObjectQtQml::Index(shape),
    qthis(0)
{
    othis = shape;
}

void ShapeQtQml::Index::classBegin()
{
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

Shape *ShapeQtQml::shape()
{
    return static_cast<Index*>(i)->othis;
}

ShapeQtQml *ShapeQtQml::fromShape(Shape *shape, QObject *parent)
{
    if(!shape) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(shape))
    {
        return static_cast<Index*>(index)->qthis;
    }

    ShapeQtQml *result = new ShapeQtQml(new Index(shape), parent);
    result->classBegin();
    return result;
}

}
