#ifndef _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_INDEX_
#define _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_INDEX_ 1

#include <osgEarthUtil/EarthManipulatorQtQml>

#include <osgGA/CameraManipulatorQtQmlIndex>

namespace osgEarth { namespace Util {

class OSGQTQML_EXPORT EarthManipulatorQtQml::Index : public osgGA::CameraManipulatorQtQml::Index
{
public:
    typedef EarthManipulator OType;
    typedef EarthManipulatorQtQml QType;
    friend class EarthManipulatorQtQml;

public:
    Index(EarthManipulator *o = 0);

    void classBegin();
};

} }

#endif // _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_INDEX_
