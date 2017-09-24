#include "module.hpp"

#include "elevationlayer.hpp"
#include "geotransform.hpp"
#include "imagelayer.hpp"
#include "layermanager.hpp"
#include "mapnode.hpp"
#include "memory.hpp"
#include "terraineffect.hpp"
#include "terrainlayer.hpp"
#include "version.hpp"
#include <QtQml>
#include <osgQtQuick/Version>

#include <QDebug>

namespace osgEarth {

void registerQtQmlTypes(const char* uri)
{

    qmlRegisterType<GeoTransformQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "GeoTransform");
    qmlRegisterType<TerrainEffectQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "TerrainEffect");
    qmlRegisterType<MapNodeQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "MapNode");

    qmlRegisterType<TerrainLayerQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "TerrainLayer");

    qmlRegisterType<ImageLayerQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "ImageLayer");

    qmlRegisterType<ElevationLayerQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "ElevationLayer");

    qmlRegisterType<LayerManagerQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "LayerManager");
    qmlRegisterSingletonType<MemoryQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "Memory", memoryQObjectSingletonTypeProvider);

    qmlRegisterSingletonType<VersionQtQml>(
        uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
        "Version", versionQObjectSingletonTypeProvider);
}
}
