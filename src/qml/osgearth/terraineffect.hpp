#ifndef _OSGEARTH_TERRAIN_EFFECT_QTQML_
#define _OSGEARTH_TERRAIN_EFFECT_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osgEarth {
class TerrainEffect;
class OSGQTQML_EXPORT TerrainEffectQtQml : public osgQtQml::Object {
    Q_OBJECT

public:
    class Index;
    TerrainEffectQtQml(QObject* parent = 0);
    TerrainEffectQtQml(Index* index, QObject* parent = 0);

    void classBegin();

    TerrainEffect* terrainEffect();
    static TerrainEffectQtQml* fromTerrainEffect(TerrainEffect* effect, QObject* parent = 0);
};
}

#endif
