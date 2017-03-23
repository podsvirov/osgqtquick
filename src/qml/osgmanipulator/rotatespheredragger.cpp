#include "rotatespheredragger.hpp"
#include "rotatespheredraggerindex.hpp"

#include <osgManipulator/RotateSphereDragger>

#include <QtCore/QDebug>

/*!
   \qmltype RotateSphereDragger
   \inherits Dragger
   \inqmlmodule osgManipulator
   \brief Dragger for performing 3D rotation on a sphere
 */

namespace osgManipulator {

RotateSphereDraggerQtQml::Index::Index(RotateSphereDragger *dragger) :
    DraggerQtQml::Index(dragger)
{
}

void RotateSphereDraggerQtQml::Index::classBegin()
{
    if(!o(this)) setO(new RotateSphereDragger);

    DraggerQtQml::Index::classBegin();
}

RotateSphereDraggerQtQml::RotateSphereDraggerQtQml(QObject *parent) :
  DraggerQtQml(parent)
{
}

RotateSphereDraggerQtQml::RotateSphereDraggerQtQml(RotateSphereDraggerQtQml::Index *index, QObject *parent) :
  DraggerQtQml(index, parent)
{
}

void RotateSphereDraggerQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    DraggerQtQml::classBegin();
}

/*!
   \qmlproperty color osgManipulator::RotateSphereDragger::color

   Color
 */

QColor RotateSphereDraggerQtQml::getColor() const
{
    return osgQt::swapColor(o(this)->getColor());
}

void RotateSphereDraggerQtQml::setColor(const QColor &color)
{
    if(color == getColor()) return;

    o(this)->setColor(osgQt::swapColor(color));

    emit colorChanged(color);
}

/*!
   \qmlproperty color osgManipulator::RotateSphereDragger::pickColor

   Pick color
 */

QColor RotateSphereDraggerQtQml::getPickColor() const
{
    return osgQt::swapColor(o(this)->getPickColor());
}

void RotateSphereDraggerQtQml::setPickColor(const QColor &color)
{
    if(color == getPickColor()) return;

    o(this)->setPickColor(osgQt::swapColor(color));

    emit pickColorChanged(color);
}

RotateSphereDragger *RotateSphereDraggerQtQml::asRotateSphereDragger()
{
    return o(this);
}

RotateSphereDraggerQtQml *RotateSphereDraggerQtQml::fromRotateSphereDragger(RotateSphereDragger *dragger, QObject *parent)
{
    if(!dragger) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(dragger))
    {
        return static_cast<RotateSphereDraggerQtQml*>(index->qtObject());
    }

    RotateSphereDraggerQtQml *result = new RotateSphereDraggerQtQml(new Index(dragger), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
