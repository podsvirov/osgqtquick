#include "module.hpp"

#include "cameramanipulatorindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml>

#include <QDebug>

namespace osgGA {

void regisgerQtQmlTypes(const char *uri)
{
    qmlRegisterUncreatableType<osgGA::CameraManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "CameraManipulator", "[osgQtQuick] CameraManipulator is Uncreatable");
}

}
