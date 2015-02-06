#include "box.hpp"
#include "boxindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QDebug>

namespace osg {

BoxQtQml::Index::Index(Box *box) :
    ShapeQtQml::Index(box),
    qthis(0)
{
    othis = box;
}

void BoxQtQml::Index::classBegin()
{
    if(!othis) othis = new Box();
    ShapeQtQml::Index::othis = othis;
    ShapeQtQml::Index::qthis = qthis;

    ShapeQtQml::Index::classBegin();
}

BoxQtQml::BoxQtQml(QObject *parent) :
  ShapeQtQml(parent)
{
}

BoxQtQml::BoxQtQml(BoxQtQml::Index *index, QObject *parent) :
  ShapeQtQml(index, parent)
{
}

void BoxQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ShapeQtQml::classBegin();
}

Box *BoxQtQml::box()
{
    return static_cast<Index*>(i)->othis;
}

BoxQtQml *BoxQtQml::fromBox(Box *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new BoxQtQml(new Index(drawable), parent);
}

}
