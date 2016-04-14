#include "tabboxdragger.hpp"
#include "tabboxdraggerindex.hpp"

#include <osgManipulator/TabBoxDragger>

#include <QDebug>

// TODO: Add CompositeDragger type as base fo TabBoxDragger

/*!
   \qmltype TabBoxDragger
   \inherits Dragger
   \inqmlmodule osgManipulator
   \brief Dragger for performing 3D rotation on a sphere
 */

namespace osgManipulator {

TabBoxDraggerQtQml::Index::Index(TabBoxDragger *dragger) :
    DraggerQtQml::Index(dragger)
{
}

void TabBoxDraggerQtQml::Index::classBegin()
{
    if(!o(this)) setO(new TabBoxDragger);

    DraggerQtQml::Index::classBegin();
}

TabBoxDraggerQtQml::TabBoxDraggerQtQml(QObject *parent) :
  DraggerQtQml(parent)
{
}

TabBoxDraggerQtQml::TabBoxDraggerQtQml(TabBoxDraggerQtQml::Index *index, QObject *parent) :
  DraggerQtQml(index, parent)
{
}

void TabBoxDraggerQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    DraggerQtQml::classBegin();
}

/*!
   \qmlproperty color osgManipulator::TabBoxDragger::pickColor

   Pick color
 */

QColor TabBoxDraggerQtQml::getPlaneColor() const
{
    return i(this)->_planeColor;
}

void TabBoxDraggerQtQml::setPlaneColor(const QColor &color)
{
    if(color == getPlaneColor()) return;

    o(this)->setPlaneColor(osgQt::swapColor(color));

    emit planeColorChanged(color);
}

TabBoxDragger *TabBoxDraggerQtQml::asTabBoxDragger()
{
    return o(this);
}

TabBoxDraggerQtQml *TabBoxDraggerQtQml::fromTabBoxDragger(TabBoxDragger *dragger, QObject *parent)
{
    if(!dragger) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(dragger))
    {
        return static_cast<TabBoxDraggerQtQml*>(index->qtObject());
    }

    TabBoxDraggerQtQml *result = new TabBoxDraggerQtQml(new Index(dragger), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
