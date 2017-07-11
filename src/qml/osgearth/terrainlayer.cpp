#include "terrainlayer.hpp"
#include "terrainlayerindex.hpp"
#include <osgEarth/TerrainLayer>

namespace osgEarth {
// TerrainLayerQtQml
TerrainLayerQtQml::Index::Index(TerrainLayer* layer)
    : osgQtQml::Index(layer)
{
}

void TerrainLayerQtQml::Index::classBegin()
{
}

TerrainLayerQtQml::TerrainLayerQtQml(QObject* parent)
    : osgQtQml::Object(parent)
{
}

TerrainLayerQtQml::TerrainLayerQtQml(TerrainLayerQtQml::Index* index, QObject* parent)
    : osgQtQml::Object(index, parent)
{
}

void TerrainLayerQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

QString TerrainLayerQtQml::name()
{
    return QString::fromStdString(o(this)->getName());
}

bool TerrainLayerQtQml::visible()
{
    return o(this)->getVisible();
}

TerrainLayer* TerrainLayerQtQml::terrainLayer()
{
    return o(this);
}

TerrainLayerQtQml* TerrainLayerQtQml::fromTerrainLayer(TerrainLayer* layer, QObject* parent)
{
    if (!layer)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(layer)) {
        return static_cast<TerrainLayerQtQml*>(index->qtObject());
    }

    TerrainLayerQtQml* result = new TerrainLayerQtQml(new Index(layer), parent);
    result->classBegin();

    return result;
}

void TerrainLayerQtQml::setVisible(bool visible)
{
    if (!isComplete()) {
        i(this)->visible = visible;
        return;
    }
    i(this)->visible = visible;
    o(this)->setVisible(visible);
}
}
