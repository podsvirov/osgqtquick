#include "earthmanipulator.hpp"
#include "earthmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgEarthUtil/EarthManipulator>

#include <QDebug>

namespace osgEarth { namespace Util {

EarthManipulatorQtQml::Index::Index(EarthManipulator *manipulator) :
    osgGA::CameraManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void EarthManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new EarthManipulator();
    CameraManipulatorQtQml::Index::othis = othis;
    CameraManipulatorQtQml::Index::qthis = qthis;

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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    CameraManipulatorQtQml::classBegin();
}

void EarthManipulatorQtQml::pan(double dx, double dy)
{
    static_cast<Index*>(i)->othis->pan(dx, dy);
}

void EarthManipulatorQtQml::rotate(double dx, double dy)
{
    static_cast<Index*>(i)->othis->rotate(dx, dy);
}

void EarthManipulatorQtQml::zoom(double dx, double dy)
{
    static_cast<Index*>(i)->othis->zoom(dx, dy);
}

EarthManipulator *EarthManipulatorQtQml::earthManipulator()
{
    return static_cast<Index*>(i)->othis;
}

EarthManipulatorQtQml *EarthManipulatorQtQml::fromEarthManipulator(EarthManipulator *manipulator, QObject *parent)
{
    if(!manipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(manipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new EarthManipulatorQtQml(new Index(manipulator), parent);
}

} }
