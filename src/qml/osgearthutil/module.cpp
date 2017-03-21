#include "module.hpp"

#include "earthmanipulatorindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml/QtQml>

#include <QtCore/QDebug>

namespace osgEarth { namespace Util {

void registerQtQmlTypes(const char *uri)
{
    qmlRegisterType<EarthManipulatorQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "EarthManipulator");
}

} }
