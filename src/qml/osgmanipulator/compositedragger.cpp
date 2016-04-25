#include "compositedragger.hpp"
#include "compositedraggerindex.hpp"

#include <osgManipulator/Dragger>

#include <QDebug>

// TODO: Add CompositeDragger type as base fo TabBoxDragger

/*!
   \qmltype CompositeDragger
   \inherits Dragger
   \inqmlmodule osgManipulator
   \brief Allows to create complex draggers

   CompositeDragger allows to create complex draggers that are composed of
   a hierarchy of Draggers.
 */

namespace osgManipulator {

CompositeDraggerQtQml::Index::Index(CompositeDragger *dragger) :
    DraggerQtQml::Index(dragger),
    _completeInfo(0)
{
}

CompositeDraggerQtQml::Index::~Index()
{
  if(_completeInfo) delete _completeInfo;
}

CompositeDraggerQtQml::CompositeDraggerQtQml(QObject *parent) :
  DraggerQtQml(parent)
{
}

CompositeDraggerQtQml::CompositeDraggerQtQml(CompositeDraggerQtQml::Index *index, QObject *parent) :
  DraggerQtQml(index, parent)
{
}

void CompositeDraggerQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    DraggerQtQml::classBegin();
}

bool CompositeDraggerQtQml::addDragger(DraggerQtQml *dragger)
{
    if (!isComplete())
      {
        i(this)->info()->dragger.append(dragger);
        return true;
      }
    else if (o(this)->addDragger(
          dragger->asDragger()))
      {
        emit numDraggersChanged(getNumDraggers());
        return true;
      }

    return false;
}

bool CompositeDraggerQtQml::removeDragger(DraggerQtQml *dragger)
{
    if (o(this)->removeDragger(
                dragger->asDragger()))
    {
        emit numDraggersChanged(getNumDraggers());
        return true;
    }

    return false;
}

int CompositeDraggerQtQml::getNumDraggers() const
{
    return o(this)->getNumDraggers();
}

DraggerQtQml *CompositeDraggerQtQml::getDragger(int i)
{
    return DraggerQtQml::fromDragger(o(this)->getDragger(i), this);
}

/*!
   \qmlproperty list<osgManipulator::Dragger> osgManipulator::CompositeDragger::draggers

   List of children draggers
 */

QQmlListProperty<DraggerQtQml> CompositeDraggerQtQml::draggers()
{
    return QQmlListProperty<DraggerQtQml>(this, (void*)0,
                                          CompositeDraggerQtQml::draggerAppend,
                                          CompositeDraggerQtQml::draggersCount,
                                          CompositeDraggerQtQml::draggerAt,
                                          CompositeDraggerQtQml::draggersClear);
}

CompositeDragger *CompositeDraggerQtQml::asCompositeDragger()
{
    return o(this);
}

CompositeDraggerQtQml *CompositeDraggerQtQml::fromCompositeDragger(CompositeDragger *dragger, QObject *parent)
{
    if(!dragger) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(dragger))
    {
        return static_cast<CompositeDraggerQtQml*>(index->qtObject());
    }

    CompositeDraggerQtQml *result = new CompositeDraggerQtQml(new Index(dragger), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

int CompositeDraggerQtQml::draggersCount(QQmlListProperty<DraggerQtQml> *list)
{
  return static_cast<CompositeDraggerQtQml*>(list->object)->getNumDraggers();
}

DraggerQtQml* CompositeDraggerQtQml::draggerAt(QQmlListProperty<DraggerQtQml> *list, int index)
{
  return static_cast<CompositeDraggerQtQml*>(list->object)->getDragger(index);
}

void CompositeDraggerQtQml::draggerAppend(QQmlListProperty<DraggerQtQml> *list, DraggerQtQml *dragger)
{
  static_cast<CompositeDraggerQtQml*>(list->object)->addDragger(dragger);
}

void CompositeDraggerQtQml::draggersClear(QQmlListProperty<DraggerQtQml> *list)
{
  CompositeDraggerQtQml *qdragger = static_cast<CompositeDraggerQtQml*>(list->object);
  CompositeDragger *odragger = qdragger->asCompositeDragger();
  while(odragger->getNumDraggers())
  {
      odragger->removeDragger(odragger->getDragger(odragger->getNumDraggers() - 1));
  }
  emit qdragger->numDraggersChanged(qdragger->getNumDraggers());
}

}
