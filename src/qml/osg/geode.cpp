#include "geode.hpp"
#include "geodeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Geode>

#include <QtCore/QDebug>

/*!
   \qmltype Geode
   \inherits Group
   \inqmlmodule osg
   \brief Geometry node
 */

namespace osg {

GeodeQtQml::Index::Index(Geode *geode) :
    GroupQtQml::Index(geode),
    _completeInfo(0)
{
}

GeodeQtQml::Index::~Index()
{
    if(_completeInfo) delete _completeInfo;
}

void GeodeQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Geode);

    GroupQtQml::Index::classBegin();
}

GeodeQtQml::GeodeQtQml(QObject *parent) :
  GroupQtQml(parent)
{
}

GeodeQtQml::GeodeQtQml(GeodeQtQml::Index *index, QObject *parent) :
  GroupQtQml(index, parent)
{
}

void GeodeQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    GroupQtQml::classBegin();
}

void GeodeQtQml::componentComplete()
{
    NodeQtQml::componentComplete();

    if(Index::CompleteInfo *info = i(this)->_completeInfo)
      {
        for(QList<DrawableQtQml*>::iterator it = info->drawables.begin();
            it != info->drawables.end(); ++it)
          {
            addDrawable(*it);
          }
        info->drawables.clear();
      }
}

bool GeodeQtQml::addDrawable(DrawableQtQml *drawable)
{
    if (!isComplete())
      {
        i(this)->info()->drawables.append(drawable);
        return true;
      }
    else if (o(this)->addDrawable(
          drawable->drawable()))
      {
        emit numDrawablesChanged(getNumDrawables());
        return true;
      }

    return false;
}

bool GeodeQtQml::removeDrawable(DrawableQtQml *drawable)
{
    if (o(this)->removeDrawable(
                drawable->drawable()))
      {
        emit numDrawablesChanged(getNumDrawables());
        return true;
      }

    return false;
}

bool GeodeQtQml::removeDrawables(int pos, int numDrawablesToRemove)
{
    if (pos < 0 || numDrawablesToRemove < 0) return false;

    if(o(this)->removeDrawables(
                static_cast<unsigned int>(pos),
                static_cast<unsigned int>(numDrawablesToRemove)))
    {
        emit numDrawablesChanged(getNumDrawables());
        return true;
    }

    return false;
}

int GeodeQtQml::getNumDrawables() const
{
    return o(this)->getNumDrawables();
}

DrawableQtQml *GeodeQtQml::getDrawable(int pos)
{
    return osg::DrawableQtQml::fromDrawable(o(this)->getDrawable(pos));
}

/*!
   \qmlproperty list<osg::Drawable> osg::Geode::drawables

   List of \l {osg::Drawable}{drawables}
 */

QQmlListProperty<DrawableQtQml> GeodeQtQml::drawables()
{
    return QQmlListProperty<DrawableQtQml>(this, (void*)0,
                                           GeodeQtQml::drawablesAppend,
                                           GeodeQtQml::drawablesCount,
                                           GeodeQtQml::drawablesAt,
                                           GeodeQtQml::drawablesClear);
}

Geode *GeodeQtQml::geode()
{
    return o(this);
}

GeodeQtQml *GeodeQtQml::fromGeode(Geode *group, QObject *parent)
{
    if(!group) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(group))
    {
        return static_cast<GeodeQtQml*>(index->qtObject());
    }

    GeodeQtQml *result = new GeodeQtQml(new Index(group), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

int GeodeQtQml::drawablesCount(QQmlListProperty<DrawableQtQml> *list)
{
  return static_cast<GeodeQtQml*>(list->object)->getNumDrawables();
}

DrawableQtQml* GeodeQtQml::drawablesAt(QQmlListProperty<DrawableQtQml> *list, int index)
{
  return static_cast<GeodeQtQml*>(list->object)->getDrawable(index);
}

void GeodeQtQml::drawablesAppend(QQmlListProperty<DrawableQtQml> *list, DrawableQtQml *drawable)
{
  static_cast<GeodeQtQml*>(list->object)->addDrawable(drawable);
}

void GeodeQtQml::drawablesClear(QQmlListProperty<DrawableQtQml> *list)
{
  static_cast<GeodeQtQml*>(list->object)->removeDrawables(0, drawablesCount(list));
}

}
