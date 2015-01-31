#include <QtQml>

#include <osgViewer/ModuleQtQml>
#include <osgViewer/ModuleQtQuick>

class osgViewerQtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("osgViewer"));
        // osgViewer types from osgQtQml library
        osgViewer::regisgerQtQmlTypes(uri);
        // osgViewer types from osgQtQuick library
        osgViewer::regisgerQtQuickTypes(uri);
    }
};

#include "plugin.moc"
