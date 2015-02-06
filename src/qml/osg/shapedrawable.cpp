#include "shapedrawable.hpp"
#include "shapedrawableindex.hpp"

#include <osgQtQml/Index>

#include <osg/ShapeDrawable>

#include <QDebug>

namespace osg {

ShapeDrawableQtQml::Index::Index(ShapeDrawable *drawable) :
    DrawableQtQml::Index(drawable),
    qthis(0)
{
    othis = drawable;
}

void ShapeDrawableQtQml::Index::classBegin()
{
    DrawableQtQml::Index::othis = othis;
    DrawableQtQml::Index::qthis = qthis;

    DrawableQtQml::Index::classBegin();
}

void ShapeDrawableQtQml::Index::componentComplete()
{
    if(!othis) {
        othis = shape.valid() ?
                    new ShapeDrawable(shape.get()) :
                    new ShapeDrawable();
    }

    DrawableQtQml::Index::othis = othis;
    DrawableQtQml::Index::qthis = qthis;

    DrawableQtQml::Index::componentComplete();
}

ShapeQtQml *ShapeDrawableQtQml::Index::getShape() const
{
    return ShapeQtQml::fromShape(shape.get());
}

void ShapeDrawableQtQml::Index::setShape(ShapeQtQml *shape)
{
    if(this->shape.get() == shape->shape()) return;

    this->shape = shape->shape();

    emit qthis->shapeChanged(shape);
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    DrawableQtQml::classBegin();
}

ShapeQtQml *ShapeDrawableQtQml::getShape() const
{
    return static_cast<Index*>(i)->getShape();
}

void ShapeDrawableQtQml::setShape(ShapeQtQml *shape)
{
    static_cast<Index*>(i)->setShape(shape);
}

ShapeDrawable *ShapeDrawableQtQml::shapeDrawable()
{
    return static_cast<Index*>(i)->othis;
}

ShapeDrawableQtQml *ShapeDrawableQtQml::fromShapeDrawable(ShapeDrawable *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new ShapeDrawableQtQml(new Index(drawable), parent);
}

}
