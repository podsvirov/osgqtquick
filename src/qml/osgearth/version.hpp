#ifndef _OSGEARTH_VERSION_QTQML_
#define _OSGEARTH_VERSION_QTQML_ 1

#include "../export.hpp"
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <osg/Version>
#include <osgEarth/Version>

namespace osgEarth {
class OSGQTQML_EXPORT VersionQtQml : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString osgVersion READ osgVersion)
    Q_PROPERTY(QString osgSOVersion READ osgSOVersion)
    Q_PROPERTY(QString osgEarthVersion READ osgEarthVersion)
    Q_PROPERTY(QString osgEarthSOVersion READ osgEarthSOVersion)
    Q_PROPERTY(QString osgLibraryName READ osgLibraryName)
    Q_PROPERTY(QString osgEarthLibraryName READ osgEarthLibraryName)

public:
    VersionQtQml(QObject* parent = 0)
        : QObject(parent)
    {
    }
    QString osgVersion() const
    {
        return QString(osgGetVersion());
    }
    QString osgEarthVersion() const
    {
        return QString(osgEarthGetVersion());
    }
    QString osgEarthSOVersion() const
    {
        return QString(osgEarthGetSOVersion());
    }
    QString osgSOVersion() const
    {
        return QString(osgGetSOVersion());
    }
    QString osgLibraryName() const
    {
        return QString(osgGetLibraryName());
    }
    QString osgEarthLibraryName() const
    {
        return QString(osgEarthGetLibraryName());
    }
};

static QObject* versionQObjectSingletonTypeProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    VersionQtQml* version = new VersionQtQml();
    return version;
}
}

#endif
