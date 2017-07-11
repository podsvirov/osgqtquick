#ifndef _OSGEARTHUTIL_LATLONG_FORMATTER_QTQML_
#define _OSGEARTHUTIL_LATLONG_FORMATTER_QTQML_ 1

#include "../export.hpp"
#include <QGeoCoordinate>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <osgEarthUtil/LatLongFormatter>

namespace osgEarth {
namespace Util {

    class OSGQTQML_EXPORT LatLongFormatterQtQml : public QObject {
        Q_OBJECT

    public:
        LatLongFormatterQtQml(QObject* parent = 0);

        Q_INVOKABLE QString format(QGeoCoordinate pos);

    private:
        LatLongFormatter _llf;
    };

    static QObject* latLongFormatterQObjectSingletonTypeProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        LatLongFormatterQtQml* llf = new LatLongFormatterQtQml();
        return llf;
    }
}
}

#endif
