#include "module.hpp"

#include "cameramanipulatorindex.hpp"
#include "standardmanipulatorindex.hpp"
#include "trackballmanipulatorindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml>

#include <QDebug>

namespace osgGA {

void regisgerQtQmlTypes(const char *uri)
{
    qmlRegisterUncreatableType<CameraManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "CameraManipulator", "[osgQtQuick] CameraManipulator is Uncreatable");

    qmlRegisterUncreatableType<StandardManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "StandardManipulator", "[osgQtQuick] StandardManipulator is Uncreatable");

    qmlRegisterType<TrackballManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "TrackballManipulator");
}

}
