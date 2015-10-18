#ifndef _OSGGA_FLIGHTMANIPULATOR_QTQML_INDEX_
#define _OSGGA_FLIGHTMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/FlightManipulatorQtQml>

#include <osgGA/FirstPersonManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT FlightManipulatorQtQml::Index : public FirstPersonManipulatorQtQml::Index
{
public:
    typedef FlightManipulator OType;
    typedef FlightManipulatorQtQml QType;
    friend class FlightManipulatorQtQml;

public:
    Index(FlightManipulator *o = 0);

    void classBegin();
};

}

#endif // _OSGGA_FLIGHTMANIPULATOR_QTQML_INDEX_
