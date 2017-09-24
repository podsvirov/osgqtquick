#ifndef _OSGEARTH_TERRAIN_LAYER_QTQML_
#define _OSGEARTH_TERRAIN_LAYER_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osgEarth {
class TerrainLayer;
// TerrainLayer (image or elevation layer)
class OSGQTQML_EXPORT TerrainLayerQtQml : public osgQtQml::Object {
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(bool visible READ visible WRITE setVisible)

public:
    class Index;
    TerrainLayerQtQml(QObject* parent = 0);
    TerrainLayerQtQml(Index* index, QObject* parent = 0);

    void classBegin();

    QString name();
    bool visible();

    TerrainLayer* terrainLayer();
    static TerrainLayerQtQml* fromTerrainLayer(TerrainLayer* layer, QObject* parent = 0);

public slots:
    void setVisible(bool visible);
};
}

#endif
