#include <QtQml/QtQml>

#include <osg/ModuleQtQml>

class osgQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osg"));
        // osg types from osgQtQml library
        osg::registerQtQmlTypes(uri);
    }
};

#include "plugin.moc"
