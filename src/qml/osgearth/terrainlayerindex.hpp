#ifndef _OSGEARTH_TERRAIN_LAYER_QTQML_INDEX_
#define _OSGEARTH_TERRAIN_LAYER_QTQML_INDEX_ 1

#include "terrainlayer.hpp"
#include <osg/ObjectQtQmlIndex>

namespace osgEarth {
// TerrainLayerQtQml::Index
class OSGQTQML_EXPORT TerrainLayerQtQml::Index : public osgQtQml::Index {
public:
    typedef TerrainLayer OType;
    typedef TerrainLayerQtQml QType;
    friend class TerrainLayerQtQml;

public:
    Index(TerrainLayer* o = 0);
    void classBegin();

private:
    bool visible;
};
}
#endif
