#include <QtQml/QtQml>

#include <osgDB/ModuleQtQml>

class osgDBQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgDB"));
        // osgDB types from osgQtQml library
        osgDB::registerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
