#include "flightmanipulator.hpp"
#include "flightmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/FlightManipulator>

#include <QDebug>

namespace osgGA {

FlightManipulatorQtQml::Index::Index(FlightManipulator *manipulator) :
    FirstPersonManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void FlightManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new FlightManipulator();
    FirstPersonManipulatorQtQml::Index::othis = othis;
    FirstPersonManipulatorQtQml::Index::qthis = qthis;

    FirstPersonManipulatorQtQml::Index::classBegin();
}

FlightManipulatorQtQml::FlightManipulatorQtQml(QObject *parent) :
  FirstPersonManipulatorQtQml(parent)
{
}

FlightManipulatorQtQml::FlightManipulatorQtQml(FlightManipulatorQtQml::Index *index, QObject *parent) :
  FirstPersonManipulatorQtQml(index, parent)
{
}

void FlightManipulatorQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    FirstPersonManipulatorQtQml::classBegin();
}

FlightManipulator *FlightManipulatorQtQml::flightManipulator()
{
    return static_cast<Index*>(i)->othis;
}

FlightManipulatorQtQml *FlightManipulatorQtQml::fromFlightManipulator(FlightManipulator *manipulator, QObject *parent)
{
    if(!manipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(manipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new FlightManipulatorQtQml(new Index(manipulator), parent);
}

}
