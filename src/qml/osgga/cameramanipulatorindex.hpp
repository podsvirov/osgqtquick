#ifndef _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_
#define _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osgGA/CameraManipulatorQtQml>

namespace osgGA {

class OSGQTQML_EXPORT CameraManipulatorQtQml::Index : public ObjectQtQml::Index
{
    friend class CameraManipulatorQtQml;

public:
    Index(CameraManipulator *o = 0);
    void classBegin();

protected:
    CameraManipulator *othis;
    CameraManipulatorQtQml *qthis;
};

}

#endif // _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_
