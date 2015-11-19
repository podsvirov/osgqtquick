#include <QtQml>

#include <osgManipulator/ModuleQtQml>

class osgManipulatorQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgManipulator"));
        // osgManipulator types from osgQtQml library
        osgManipulator::registerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
