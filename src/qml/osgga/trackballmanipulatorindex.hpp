#ifndef _OSGGA_TRACKBALLMANIPULATOR_QTQML_INDEX_
#define _OSGGA_TRACKBALLMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/TrackballManipulatorQtQml>

#include <osgGA/CameraManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT TrackballManipulatorQtQml::Index : public CameraManipulatorQtQml::Index
{
    friend class TrackballManipulatorQtQml;

public:
    Index(TrackballManipulator *o = 0);

    void classBegin();

protected:
    TrackballManipulator *othis;
    TrackballManipulatorQtQml *qthis;
};

}

#endif // _OSGGA_TRACKBALLMANIPULATOR_QTQML_INDEX_
