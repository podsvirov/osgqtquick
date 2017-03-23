#include "earthmanipulator.hpp"
#include "earthmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgEarthUtil/EarthManipulator>

#include <QtCore/QDebug>

namespace osgEarth { namespace Util {

EarthManipulatorQtQml::Index::Index(EarthManipulator *manipulator) :
    osgGA::CameraManipulatorQtQml::Index(manipulator)
{
}

void EarthManipulatorQtQml::Index::classBegin()
{
    if(!o(this)) setO(new EarthManipulator);

    CameraManipulatorQtQml::Index::classBegin();
}

EarthManipulatorQtQml::EarthManipulatorQtQml(QObject *parent) :
  CameraManipulatorQtQml(parent)
{
}

EarthManipulatorQtQml::EarthManipulatorQtQml(EarthManipulatorQtQml::Index *index, QObject *parent) :
  CameraManipulatorQtQml(index, parent)
{
}

void EarthManipulatorQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    CameraManipulatorQtQml::classBegin();
}

void EarthManipulatorQtQml::pan(double dx, double dy)
{
    o(this)->pan(dx, dy);
}

void EarthManipulatorQtQml::rotate(double dx, double dy)
{
    o(this)->rotate(dx, dy);
}

void EarthManipulatorQtQml::zoom(double dx, double dy)
{
    o(this)->zoom(dx, dy);
}

EarthManipulator *EarthManipulatorQtQml::earthManipulator()
{
    return o(this);
}

EarthManipulatorQtQml *EarthManipulatorQtQml::fromEarthManipulator(EarthManipulator *manipulator, QObject *parent)
{
    if(!manipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(manipulator))
    {
        return static_cast<EarthManipulatorQtQml*>(index->qtObject());
    }

    EarthManipulatorQtQml *result =  new EarthManipulatorQtQml(new Index(manipulator), parent);
    result->classBegin();
    return result;
}

} }
