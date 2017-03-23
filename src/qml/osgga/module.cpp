#include "module.hpp"

#include "cameramanipulatorindex.hpp"
#include "standardmanipulatorindex.hpp"
#include "firstpersonmanipulatorindex.hpp"
#include "flightmanipulatorindex.hpp"
#include "orbitmanipulatorindex.hpp"
#include "trackballmanipulatorindex.hpp"
#include "nodetrackermanipulatorindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml/QtQml>

#include <QtCore/QDebug>

namespace osgGA {

void registerQtQmlTypes(const char *uri)
{
    qmlRegisterUncreatableType<CameraManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "CameraManipulator", "[osgQtQuick] CameraManipulator is Uncreatable");

    qmlRegisterUncreatableType<StandardManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "StandardManipulator", "[osgQtQuick] StandardManipulator is Uncreatable");

    qmlRegisterType<FirstPersonManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "FirstPersonManipulator");

    qmlRegisterType<FlightManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "FlightManipulator");

    qmlRegisterType<OrbitManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "OrbitManipulator");

    qmlRegisterType<TrackballManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "TrackballManipulator");

    qmlRegisterType<NodeTrackerManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "NodeTrackerManipulator");
}

}
