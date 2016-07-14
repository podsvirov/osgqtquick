#include "tabplanedragger.hpp"
#include "tabplanedraggerindex.hpp"

#include <osgManipulator/TabPlaneDragger>

#include <QDebug>

// TODO: Add CompositeDragger type as base fo TabPlaneDragger

/*!
   \qmltype TabPlaneDragger
   \inherits CompositeDragger
   \inqmlmodule osgManipulator
   \brief Plane dragger consists of a plane with tabs

   Tab plane dragger consists of a plane with tabs on it's corners and edges
   for scaling.
 */

namespace osgManipulator {

TabPlaneDraggerQtQml::Index::Index(TabPlaneDragger *dragger) :
    CompositeDraggerQtQml::Index(dragger)
{
}

void TabPlaneDraggerQtQml::Index::classBegin()
{
    if(!o(this)) setO(new TabPlaneDragger);

    CompositeDraggerQtQml::Index::classBegin();
}

TabPlaneDraggerQtQml::TabPlaneDraggerQtQml(QObject *parent) :
  CompositeDraggerQtQml(parent)
{
}

TabPlaneDraggerQtQml::TabPlaneDraggerQtQml(TabPlaneDraggerQtQml::Index *index, QObject *parent) :
  CompositeDraggerQtQml(index, parent)
{
}

void TabPlaneDraggerQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    CompositeDraggerQtQml::classBegin();
}

/*!
   \qmlproperty color osgManipulator::TabPlaneDragger::planeColor

   Plane color
 */

QColor TabPlaneDraggerQtQml::getPlaneColor() const
{
    return i(this)->_planeColor;
}

void TabPlaneDraggerQtQml::setPlaneColor(const QColor &color)
{
    if(color == getPlaneColor()) return;

    o(this)->setPlaneColor(osgQt::swapColor(color));

    emit planeColorChanged(color);
}

TabPlaneDragger *TabPlaneDraggerQtQml::asTabPlaneDragger()
{
    return o(this);
}

TabPlaneDraggerQtQml *TabPlaneDraggerQtQml::fromTabPlaneDragger(TabPlaneDragger *dragger, QObject *parent)
{
    if(!dragger) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(dragger))
    {
        return static_cast<TabPlaneDraggerQtQml*>(index->qtObject());
    }

    TabPlaneDraggerQtQml *result = new TabPlaneDraggerQtQml(new Index(dragger), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
