#include "flightmanipulator.hpp"
#include "flightmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/FlightManipulator>

#include <QtCore/QDebug>

/*!
   \qmltype FlightManipulator
   \inherits FirstPersonManipulator
   \inqmlmodule osgGA
   \brief Flight simulator-like camera control
 */

namespace osgGA {

FlightManipulatorQtQml::Index::Index(FlightManipulator *manipulator) :
    FirstPersonManipulatorQtQml::Index(manipulator)
{
}

void FlightManipulatorQtQml::Index::classBegin()
{
    if(!o(this)) setO(new FlightManipulator);

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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    FirstPersonManipulatorQtQml::classBegin();
}

FlightManipulator *FlightManipulatorQtQml::flightManipulator()
{
    return o(this);
}

FlightManipulatorQtQml *FlightManipulatorQtQml::fromFlightManipulator(FlightManipulator *manipulator, QObject *parent)
{
    if(!manipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(manipulator))
    {
        return static_cast<FlightManipulatorQtQml*>(index->qtObject());
    }

    FlightManipulatorQtQml *result = new FlightManipulatorQtQml(new Index(manipulator), parent);
    result->classBegin();
    return result;
}

}
