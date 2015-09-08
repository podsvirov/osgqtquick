// Qt headers
#include <QGuiApplication>
#include <QQuickView>

#include <QQmlContext>
#include <QDateTime>

// osgQtQuick
#include <osg/ModuleQtQml>
#include <osgDB/ModuleQtQml>
#include <osgGA/ModuleQtQml>
#include <osgViewer/ModuleQtQml>
#include <osgViewer/ModuleQtQuick>
#if defined(OSGQTQUICK_WITH_EARTH)
#include <osgEarthUtil/ModuleQtQml>
#endif

#ifdef DETECT_MEMORY_LEAKS
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif /* _DEBUG */
#endif /* DETECT_MEMORY_LEAKS */

int main(int argc, char *argv[])
{
    // used for memory leak detection
    #ifdef DETECT_MEMORY_LEAKS
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    // Create application object
    QGuiApplication app(argc, argv);

    // Register modules
    osg::regisgerQtQmlTypes("osg");
    osgDB::regisgerQtQmlTypes("osgDB");
    osgGA::regisgerQtQmlTypes("osgGA");
    osgViewer::regisgerQtQmlTypes("osgViewer");
    osgViewer::regisgerQtQuickTypes("osgViewer");
#if defined(OSGQTQUICK_WITH_EARTH)
    osgEarth::Util::regisgerQtQmlTypes("osgEarthUtil");
#endif

    // Create Viewer and load qml script
    QQuickView view;

    view.resize(800, 600);
    view.setResizeMode(QQuickView::SizeRootObjectToView);

#if defined(OSGQTQUICK_DEBUGGED_SCRIPT)
    view.setSource(QUrl::fromLocalFile(OSGQTQUICK_DEBUGGED_SCRIPT));
#endif

    view.show();

    // Start loop
    return app.exec();
}
