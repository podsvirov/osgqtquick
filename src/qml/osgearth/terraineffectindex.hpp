#ifndef _OSGEARTH_TERRAIN_EFFECT_QTQML_INDEX_
#define _OSGEARTH_TERRAIN_EFFECT_QTQML_INDEX_ 1

#include "terraineffect.hpp"
#include <osg/ObjectQtQmlIndex>

namespace osgEarth {
class OSGQTQML_EXPORT TerrainEffectQtQml::Index : public osgQtQml::Index {
public:
    typedef TerrainEffect OType;
    typedef TerrainEffectQtQml QType;
    friend class TerrainEffectQtQml;

public:
    Index(TerrainEffect* o = 0);
    void classBegin();
};
}

#endif
