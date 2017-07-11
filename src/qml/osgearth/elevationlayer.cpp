#include "elevationlayer.hpp"
#include "elevationlayerindex.hpp"
#include <osgEarth/ElevationLayer>

namespace osgEarth {

// ElevationLayer
ElevationLayerQtQml::Index::Index(ElevationLayer* layer)
    : TerrainLayerQtQml::Index(layer)
{
}

void ElevationLayerQtQml::Index::classBegin()
{
    TerrainLayerQtQml::Index::classBegin();
}

ElevationLayerQtQml::ElevationLayerQtQml(QObject* parent)
    : TerrainLayerQtQml(parent)
{
}

ElevationLayerQtQml::ElevationLayerQtQml(ElevationLayerQtQml::Index* index, QObject* parent)
    : TerrainLayerQtQml(index, parent)
{
}

void ElevationLayerQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    TerrainLayerQtQml::classBegin();
}

ElevationLayer* ElevationLayerQtQml::elevationLayer()
{
    return o(this);
}

ElevationLayerQtQml* ElevationLayerQtQml::fromElevationLayer(ElevationLayer* layer, QObject* parent)
{
    if (!layer)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(layer)) {
        return static_cast<ElevationLayerQtQml*>(index->qtObject());
    }

    ElevationLayerQtQml* result = new ElevationLayerQtQml(new Index(layer), parent);
    result->classBegin();

    return result;
}
}
