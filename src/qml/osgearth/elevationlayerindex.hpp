#ifndef _OSGEARTH_ELEVATION_LAYER_QTQML_INDEX_
#define _OSGEARTH_ELEVATION_LAYER_QTQML_INDEX_ 1

#include "terrainlayerindex.hpp"

namespace osgEarth {
// ElevationLayerQtQml::Index
class OSGQTQML_EXPORT ElevationLayerQtQml::Index : public TerrainLayerQtQml::Index {
public:
    typedef ElevationLayer OType;
    typedef ElevationLayerQtQml QType;
    friend class ElevationLayerQtQml;

public:
    Index(ElevationLayer* o = 0);
    void classBegin();
};
}

#endif
