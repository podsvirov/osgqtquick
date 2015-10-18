#include "orbitmanipulator.hpp"
#include "orbitmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/OrbitManipulator>

#include <QDebug>

/*!
   \qmltype OrbitManipulator
   \inherits StandardManipulator
   \inqmlmodule osgGA
   \brief Manipulator based on focal center, distance from the center,
   and orientation of distance vector to the eye
 */

namespace osgGA {

OrbitManipulatorQtQml::Index::Index(OrbitManipulator *manipulator) :
    StandardManipulatorQtQml::Index(manipulator)
{
}

void OrbitManipulatorQtQml::Index::classBegin()
{
    if(!o(this)) setO(new OrbitManipulator);

    StandardManipulatorQtQml::Index::classBegin();
}

OrbitManipulatorQtQml::OrbitManipulatorQtQml(QObject *parent) :
  StandardManipulatorQtQml(parent)
{
}

OrbitManipulatorQtQml::OrbitManipulatorQtQml(OrbitManipulatorQtQml::Index *index, QObject *parent) :
  StandardManipulatorQtQml(index, parent)
{
}

void OrbitManipulatorQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    StandardManipulatorQtQml::classBegin();
}

qreal OrbitManipulatorQtQml::getWheelZoomFactor() const
{
    return static_cast<qreal>(o(this)->getWheelZoomFactor());
}

void OrbitManipulatorQtQml::setWheelZoomFactor(qreal wheelZoomFactor)
{
    if (getWheelZoomFactor() == wheelZoomFactor) return;

    o(this)->setWheelZoomFactor(static_cast<float>(wheelZoomFactor));

    emit wheelZoomFactorChanged(wheelZoomFactor);
}

OrbitManipulator *OrbitManipulatorQtQml::orbitManipulator()
{
    return o(this);
}

OrbitManipulatorQtQml *OrbitManipulatorQtQml::fromOrbitManipulator(OrbitManipulator *ortitManipulator, QObject *parent)
{
    if(!ortitManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(ortitManipulator))
    {
        return static_cast<OrbitManipulatorQtQml*>(index->qtObject());
    }

    OrbitManipulatorQtQml *result = new OrbitManipulatorQtQml(new Index(ortitManipulator), parent);
    result->classBegin();
    return result;
}

}
