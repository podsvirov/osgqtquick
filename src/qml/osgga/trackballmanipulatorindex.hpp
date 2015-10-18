#ifndef _OSGGA_TRACKBALLMANIPULATOR_QTQML_INDEX_
#define _OSGGA_TRACKBALLMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/TrackballManipulatorQtQml>

#include <osgGA/OrbitManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT TrackballManipulatorQtQml::Index : public OrbitManipulatorQtQml::Index
{
public:
    typedef TrackballManipulator OType;
    typedef TrackballManipulatorQtQml QType;
    friend class TrackballManipulatorQtQml;

public:
    Index(TrackballManipulator *o = 0);

    void classBegin();
};

}

#endif // _OSGGA_TRACKBALLMANIPULATOR_QTQML_INDEX_
