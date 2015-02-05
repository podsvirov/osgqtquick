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
    if(!othis) othis = new ShapeDrawable();
    DrawableQtQml::Index::othis = othis;
    DrawableQtQml::Index::qthis = qthis;

    DrawableQtQml::Index::classBegin();
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
