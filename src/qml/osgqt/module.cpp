#include "module.hpp"

#include "qfontimplementationindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml/QtQml>

#include <QtCore/QDebug>

namespace osgQt {

void registerQtQmlTypes(const char *uri)
{
    qmlRegisterType<QFontImplementationQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "QFontImplementation");
}

}
