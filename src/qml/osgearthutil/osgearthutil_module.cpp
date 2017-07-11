#include "module.hpp"

#include "activitymonitortool.hpp"
#include "contourmap.hpp"
#include "earthmanipulatorindex.hpp"
#include "geodeticgraticule.hpp"
#include "latlongformatter.hpp"
#include "measuretoolhandler.hpp"
#include "mousecoordstool.hpp"
#include "objectlocator.hpp"
#include "oceannode.hpp"
#include "skynode.hpp"
#include "terrainprofileanalysistool.hpp"
#include "verticalscale.hpp"
#include "viewcoordstool.hpp"
#include <QtQml>
#include <osgQtQuick/Version>

#include <QDebug>

namespace osgEarth {
namespace Util {

    void registerQtQmlTypes(const char* uri)
    {
        qmlRegisterType<EarthManipulatorQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "EarthManipulator");
        qmlRegisterType<SkyNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "SkyNode");
        qmlRegisterType<OceanNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "OceanNode");
        qmlRegisterType<ObjectLocatorNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "ObjectLocatorNode");
        qmlRegisterType<MouseCoordsToolQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "MouseCoordsTool");
        qmlRegisterType<TerrainProfileAnalysisToolQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "TerrainProfileAnalysisTool");
        qmlRegisterType<GeodeticGraticuleQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "GeodeticGraticule");
        qmlRegisterType<VerticalScaleQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "VerticalScale");
        qmlRegisterType<ViewCoordsToolQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "ViewCoordsTool");
        qmlRegisterType<MeasureRecordQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "MeasureRecord");
        qmlRegisterType<MeasureToolHandlerQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "MeasureToolHandler");
        qmlRegisterType<ContourMapQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "ContourMap");
        qmlRegisterType<ActivityMonitorToolQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "ActivityMonitorTool");
        qmlRegisterSingletonType<LatLongFormatterQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "LatLongFormatter", latLongFormatterQObjectSingletonTypeProvider);
    }
}
}
