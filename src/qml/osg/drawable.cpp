#include "drawable.hpp"
#include "drawableindex.hpp"

#include <osgQtQml/Index>

#include <osg/Drawable>

namespace osg {

DrawableQtQml::Index::Index(Drawable *drawable) :
    ObjectQtQml::Index(drawable),
    qthis(0)
{
    othis = drawable;
}

void DrawableQtQml::Index::classBegin()
{
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

void DrawableQtQml::Index::componentComplete()
{
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::componentComplete();
}

DrawableQtQml::DrawableQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

DrawableQtQml::DrawableQtQml(DrawableQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void DrawableQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

Drawable *DrawableQtQml::drawable()
{
    return static_cast<Index*>(i)->othis;
}

DrawableQtQml *DrawableQtQml::fromDrawable(Drawable *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<Index*>(index)->qthis;
    }

    DrawableQtQml *result = new DrawableQtQml(new Index(drawable), parent);
    result->classBegin();
    return result;
}

}
