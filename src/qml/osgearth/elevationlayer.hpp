#ifndef _OSGEARTH_ELEVATION_LAYER_QTQML_
#define _OSGEARTH_ELEVATION_LAYER_QTQML_ 1

#include "terrainlayer.hpp"

namespace osgEarth {

class ElevationLayer;
// ElevationLayer
class OSGQTQML_EXPORT ElevationLayerQtQml : public TerrainLayerQtQml {
    Q_OBJECT

public:
    class Index;
    ElevationLayerQtQml(QObject* parent = 0);
    ElevationLayerQtQml(Index* index, QObject* parent = 0);

    void classBegin();

    ElevationLayer* elevationLayer();
    static ElevationLayerQtQml* fromElevationLayer(ElevationLayer* layer, QObject* parent = 0);
};
}

#endif
