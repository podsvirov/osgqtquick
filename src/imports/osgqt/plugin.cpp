#include <QtQml/QtQml>

#include <osgQt/ModuleQtQml>

class osgQtQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgQt"));
        // osgQt types from osgQtQml library
        osgQt::registerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
