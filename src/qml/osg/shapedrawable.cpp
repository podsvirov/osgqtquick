#include "shapedrawable.hpp"
#include "shapedrawableindex.hpp"

#include <osgQtQml/Index>

#include <osg/ShapeDrawable>

#include <QDebug>

/*!
   \qmltype ShapeDrawable
   \inherits Drawable
   \inqmlmodule osg
   \brief Allow the use of \l {osg::Shape}{Shapes} as \l {osg::Drawable}{Drawables}
 */

namespace osg {

ShapeDrawableQtQml::Index::Index(ShapeDrawable *drawable) :
    DrawableQtQml::Index(drawable)
{
}

void ShapeDrawableQtQml::Index::componentComplete()
{
    if(!o(this)) {
        setO(shape.valid()
             ? new ShapeDrawable(shape.get())
             : new ShapeDrawable);
    }

    DrawableQtQml::Index::componentComplete();

    setColor(color);
}

/*!
   \qmlproperty osg::Shape osg::ShapeDrawable::shape

   Rendered \l {osg::Shape}{shape}
 */

ShapeQtQml *ShapeDrawableQtQml::Index::getShape() const
{
    return ShapeQtQml::fromShape(shape.get());
}

void ShapeDrawableQtQml::Index::setShape(ShapeQtQml *shape)
{
    if(this->shape.get() == shape->shape()) return;

    this->shape = shape->shape();

    emit q(this)->shapeChanged(shape);
}

/*!
   \qmlproperty color osg::ShapeDrawable::color

   Color of \l {osg::Shape}{shape}
 */

void ShapeDrawableQtQml::Index::setColor(const QColor &color)
{
    if(!isComplete())
    {
        this->color = color;
        return;
    }

    osg::Vec4 c = osgQt::swapColor(color);

    if(o(this)->getColor() == c) return;

    o(this)->setColor(c);

    emit q(this)->colorChanged(color);
}

ShapeDrawableQtQml::ShapeDrawableQtQml(QObject *parent) :
  DrawableQtQml(parent)
{
}

ShapeDrawableQtQml::ShapeDrawableQtQml(ShapeDrawableQtQml::Index *index, QObject *parent) :
  DrawableQtQml(index, parent)
{
}

void ShapeDrawableQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    DrawableQtQml::classBegin();
}

ShapeQtQml *ShapeDrawableQtQml::getShape() const
{
    return i(this)->getShape();
}

void ShapeDrawableQtQml::setShape(ShapeQtQml *shape)
{
    i(this)->setShape(shape);
}

QColor ShapeDrawableQtQml::getColor() const
{
    return osgQt::swapColor(o(this)->getColor());
}

void ShapeDrawableQtQml::setColor(const QColor &color)
{
    i(this)->setColor(color);
}

ShapeDrawable *ShapeDrawableQtQml::shapeDrawable()
{
    return o(this);
}

ShapeDrawableQtQml *ShapeDrawableQtQml::fromShapeDrawable(ShapeDrawable *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<ShapeDrawableQtQml*>(index->qtObject());
    }

    return new ShapeDrawableQtQml(new Index(drawable), parent);
}

}
