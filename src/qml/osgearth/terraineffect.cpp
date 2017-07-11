#include "terraineffect.hpp"
#include "terraineffectindex.hpp"
#include <osgEarth/TerrainEffect>

namespace osgEarth {

TerrainEffectQtQml::Index::Index(TerrainEffect* effect)
    : osgQtQml::Index(effect)
{
}

void TerrainEffectQtQml::Index::classBegin()
{
    //    if (!o(this)) {
    //        setO(new TerrainEffect());
    //    }
    //    osgQtQml::Index::classBegin();
}

TerrainEffectQtQml::TerrainEffectQtQml(QObject* parent)
    : osgQtQml::Object(parent)
{
}

TerrainEffectQtQml::TerrainEffectQtQml(TerrainEffectQtQml::Index* index, QObject* parent)
    : osgQtQml::Object(index, parent)
{
}

void TerrainEffectQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

TerrainEffect* TerrainEffectQtQml::terrainEffect()
{
    return o(this);
}

TerrainEffectQtQml* TerrainEffectQtQml::fromTerrainEffect(TerrainEffect* effect, QObject* parent)
{
    if (!effect)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(effect)) {
        return static_cast<TerrainEffectQtQml*>(index->qtObject());
    }

    TerrainEffectQtQml* result = new TerrainEffectQtQml(new Index(effect), parent);
    result->classBegin();
    return result;
}
}
