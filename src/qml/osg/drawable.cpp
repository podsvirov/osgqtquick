#include "drawable.hpp"
#include "drawableindex.hpp"

#include <osgQtQml/Index>

#include <osg/Drawable>

/*!
   \qmltype Drawable
   \inherits Node
   \inqmlmodule osg
   \brief Base type for drawable geometry
 */

namespace osg {

DrawableQtQml::Index::Index(Drawable *drawable) :
    NodeQtQml::Index(drawable)
{
}

void DrawableQtQml::Index::classBegin()
{
    // Do nothing. Drawable is Uncreatable.
}

DrawableQtQml::DrawableQtQml(QObject *parent) :
  NodeQtQml(parent)
{
}

DrawableQtQml::DrawableQtQml(DrawableQtQml::Index *index, QObject *parent) :
  NodeQtQml(index, parent)
{
}

void DrawableQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    NodeQtQml::classBegin();
}

Drawable *DrawableQtQml::drawable()
{
    return o(this);
}

DrawableQtQml *DrawableQtQml::fromDrawable(Drawable *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<DrawableQtQml*>(index->qtObject());
    }

    DrawableQtQml *result = new DrawableQtQml(new Index(drawable), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
