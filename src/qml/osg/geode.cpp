#include "geode.hpp"
#include "geodeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Geode>

#include <QDebug>

/*!
   \qmltype Geode
   \inherits osg::Node
   \inqmlmodule osg
   \brief Geometry node
 */

namespace osg {

GeodeQtQml::Index::Index(Geode *group) :
    NodeQtQml::Index(group),
    qthis(0),
    _completeInfo(0)
{
    othis = group;
}

GeodeQtQml::Index::~Index()
{
    if(_completeInfo) delete _completeInfo;
}

void GeodeQtQml::Index::classBegin()
{
    if(!othis) othis = new Geode();
    NodeQtQml::Index::othis = othis;
    NodeQtQml::Index::qthis = qthis;

    NodeQtQml::Index::classBegin();
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

void GeodeQtQml::componentComplete()
{
    NodeQtQml::componentComplete();

    if(Index::CompleteInfo *info = static_cast<Index*>(i)->_completeInfo)
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
        static_cast<Index*>(i)->info()->drawables.append(drawable);
        return true;
      }
    else if (static_cast<GeodeQtQml::Index*>(i)->othis->addDrawable(
          static_cast<osg::Drawable*>(drawable->index()->osgReferenced())))
      {
        emit numDrawablesChanged(getNumDrawables());
        return true;
      }

    return false;
}

bool GeodeQtQml::removeDrawable(DrawableQtQml *drawable)
{
    if (static_cast<GeodeQtQml::Index*>(i)->othis->removeDrawable(
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

    if(static_cast<Index*>(i)->othis->removeDrawables(
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
    return static_cast<Index*>(i)->othis->getNumDrawables();
}

DrawableQtQml *GeodeQtQml::getDrawable(int pos)
{
    return osg::DrawableQtQml::fromDrawable(static_cast<Index*>(i)->othis->getDrawable(pos));
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
