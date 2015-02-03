#include "module.hpp"

#include "loaderindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml>

#include <QDebug>

namespace osgDB {

void regisgerQtQmlTypes(const char *uri)
{
    qmlRegisterType<LoaderQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Loader");
}

}
