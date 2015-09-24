#include <QtQml>

#include <osgGA/ModuleQtQml>

class osgGAQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgGA"));
        // osgGA types from osgQtQml library
        osgGA::registerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
