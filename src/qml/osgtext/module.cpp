#include "module.hpp"

#include "styleindex.hpp"
#include "fontindex.hpp"
#include "textbaseindex.hpp"
#include "text3dindex.hpp"

#include <osgQtQuick/Version>
#include <QtQml>

#include <QDebug>

namespace osgText {

void registerQtQmlTypes(const char *uri)
{
    qmlRegisterType<StyleQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Style");

    qmlRegisterType<FontQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Font");

    qmlRegisterUncreatableType<TextBaseQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "TextBase", "[osgQtQuick] TextBase is Uncreatable");

    qmlRegisterType<Text3DQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Text3D");
}

}
