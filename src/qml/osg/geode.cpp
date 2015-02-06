#include "geode.hpp"
#include "geodeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Geode>

#include <QDebug>

namespace osg {

GeodeQtQml::Index::Index(Geode *group) :
    NodeQtQml::Index(group),
    qthis(0)
{
    othis = group;
}

void GeodeQtQml::Index::classBegin()
{
    if(!othis) othis = new Geode();
    NodeQtQml::Index::othis = othis;
    NodeQtQml::Index::qthis = qthis;

    NodeQtQml::Index::classBegin();
}

bool GeodeQtQml::Index::addDrawable(DrawableQtQml *drawable)
{
    osg::Drawable *a = drawable->drawable();

    if(!a) return false;

    return othis->addDrawable(a);
}

bool GeodeQtQml::Index::removeDrawable(DrawableQtQml *drawable)
{
    osg::Drawable *a = drawable->drawable();

    if(!a) return false;

    return othis->removeDrawable(a);
}

GeodeQtQml::GeodeQtQml(QObject *parent) :
  NodeQtQml(parent)
{
}

GeodeQtQml::GeodeQtQml(GeodeQtQml::Index *index, QObject *parent) :
  NodeQtQml(index, parent)
{
}

void GeodeQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    NodeQtQml::classBegin();
}

bool GeodeQtQml::addDrawable(DrawableQtQml *drawable)
{
    if (static_cast<Index*>(i)->addDrawable(drawable))
    {
        emit numDrawablesChanged(getNumDrawables());
        return true;
    }

    return false;
}

bool GeodeQtQml::removeDrawable(DrawableQtQml *drawable)
{
    if (static_cast<GeodeQtQml::Index*>(i)->removeDrawable(drawable))
    {
        emit numDrawablesChanged(getNumDrawables());
        return true;
    }

    return false;
}

int GeodeQtQml::getNumDrawables() const
{
    return static_cast<Index*>(i)->othis->getNumDrawables();
}

Geode *GeodeQtQml::geode()
{
    return static_cast<Index*>(i)->othis;
}

GeodeQtQml *GeodeQtQml::fromGeode(Geode *group, QObject *parent)
{
    if(!group) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(group))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new GeodeQtQml(new Index(group), parent);
}

}
