#ifndef _OSGEARTH_LAYER_MANAGER_QTQML_
#define _OSGEARTH_LAYER_MANAGER_QTQML_ 1

#include <QQmlListProperty>

#include "elevationlayer.hpp"
#include "imagelayer.hpp"
#include "terrainlayer.hpp"
#include <osgEarth/Map>
#include <osgEarth/MapFrame>
#include <osgEarth/MapNode>
#include <osgEarth/MapNodeQtQml>

namespace osgEarth {

// LayerManager
class LayerManager : public osg::Referenced {
public:
    LayerManager(MapNode* mapNode);

    const ImageLayerVector& imageLayers();
    const ElevationLayerVector& elevationLayers();

    ImageLayer* getImageLayerAt(int index) const;
    ImageLayer* getImageLayerByName(const std::string& name) const;

    ElevationLayer* getElevationLayerByName(const std::string& name) const;
    ElevationLayer* getElevationLayerAt(int index) const;

    void removetImageLayerByName(const std::string& name);
    void removetElevationLayerByName(const std::string& name);

    void addImageLayer(ImageLayer* layer);
    void addElevationLayer(ElevationLayer* layer);

    void clearImageLayers();
    void clearElevationLayers();

private:
    MapNode* _mapNode;
    osg::ref_ptr<Map> _activeMap;
    MapFrame _mapFrame;
};

// LayerManagerQtQml
class OSGQTQML_EXPORT LayerManagerQtQml : public osgQtQml::Object {
    Q_OBJECT
    Q_PROPERTY(MapNodeQtQml* mapNode READ mapNode WRITE setMapNode)
    Q_PROPERTY(int numImageLayers READ getNumImagelayer NOTIFY numImageLayersChanged)
    Q_PROPERTY(int numElevationLayers READ getNumElevationLayer NOTIFY numElevationLayersChanged)
    Q_PROPERTY(QQmlListProperty<osgEarth::ImageLayerQtQml> imageLayers READ imageLayers NOTIFY numImageLayersChanged)
    Q_PROPERTY(QQmlListProperty<osgEarth::ElevationLayerQtQml> elevationLayers READ elevationLayers NOTIFY numElevationLayersChanged)

    //    Q_CLASSINFO("DefaultProperty", "imagelayers")

    MapNodeQtQml* m_mapNode;

public:
    class Index;
    LayerManagerQtQml(QObject* parent = 0);
    LayerManagerQtQml(Index* index, QObject* parent = 0);

    void classBegin();
    void componentComplete();

    QQmlListProperty<ImageLayerQtQml> imageLayers();
    QQmlListProperty<ElevationLayerQtQml> elevationLayers();

    Q_INVOKABLE int getNumImagelayer();
    Q_INVOKABLE int getNumElevationLayer();
    Q_INVOKABLE ImageLayerQtQml* getImageLayer(int index);
    Q_INVOKABLE ElevationLayerQtQml* getElevationLayer(int index);
    Q_INVOKABLE bool addImageLayer(ImageLayerQtQml* layer);
    Q_INVOKABLE bool addElevationLayer(ElevationLayerQtQml* layer);
    Q_INVOKABLE void clearImageLayers();
    Q_INVOKABLE void clearElevationLayers();
    Q_INVOKABLE QString getImageLayerName(int index);
    Q_INVOKABLE QString getElevationLayerName(int index);
    Q_INVOKABLE void setImageLayerVisible(int index, bool visible);
    Q_INVOKABLE void setImageLayerVisibleByName(QString name, bool visible);
    Q_INVOKABLE void setElevationLayerVisible(int index, bool visible);
    Q_INVOKABLE void setElevationLayerVisibleByName(QString name, bool visible);

    MapNodeQtQml* mapNode();

    LayerManager* layerManager();
    static LayerManagerQtQml* fromLayerManager(LayerManager* mgr, QObject* parent = 0);

public slots:
    void setMapNode(MapNodeQtQml* mapNode);

signals:
    void numImageLayersChanged(int numImageLayers);
    void numElevationLayersChanged(int numElevationLayers);

protected:
    static int imageLayersCount(QQmlListProperty<ImageLayerQtQml>* list);
    static ImageLayerQtQml* imageLayersAt(QQmlListProperty<ImageLayerQtQml>* list, int index);
    static void imageLayersAppend(QQmlListProperty<ImageLayerQtQml>* list, ImageLayerQtQml* layer);
    static void imageLayersClear(QQmlListProperty<ImageLayerQtQml>* list);

    static int elevationLayersCount(QQmlListProperty<ElevationLayerQtQml>* list);
    static ElevationLayerQtQml* elevationLayersAt(QQmlListProperty<ElevationLayerQtQml>* list, int index);
    static void elevationLayersAppend(QQmlListProperty<ElevationLayerQtQml>* list, ElevationLayerQtQml* layer);
    static void elevationLayersClear(QQmlListProperty<ElevationLayerQtQml>* list);
};
}

#endif
