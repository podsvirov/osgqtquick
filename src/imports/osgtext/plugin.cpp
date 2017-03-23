#include <QtQml/QtQml>

#include <osgText/ModuleQtQml>

class osgTextQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgText"));
        // osgText types from osgQtQml library
        osgText::registerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
