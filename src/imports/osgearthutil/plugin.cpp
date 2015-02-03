#include <QtQml>

#include <osgEarthUtil/ModuleQtQml>

class osgEarthUtilQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgEarthUtil"));
        // osgEarth::Util types from osgQtQml library
        osgEarth::Util::regisgerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
