#include "layermanager.hpp"
#include "layermanagerindex.hpp"

namespace osgEarth {

// LayerManager
LayerManager::LayerManager(MapNode* mapNode)
    : _mapNode(mapNode)
{
    if (mapNode) {
        _activeMap = mapNode->getMap();
        _mapFrame.setMap(_activeMap);
    }
}

const ElevationLayerVector& LayerManager::elevationLayers()
{
    return _mapFrame.elevationLayers();
}

const ImageLayerVector& LayerManager::imageLayers()
{
    return _mapFrame.imageLayers();
}

ImageLayer* LayerManager::getImageLayerAt(int index) const
{
    return _mapFrame.getImageLayerAt(index);
}

ImageLayer* LayerManager::getImageLayerByName(const std::string& name) const
{
    return _mapFrame.getImageLayerByName(name);
}

ElevationLayer* LayerManager::getElevationLayerByName(const std::string& name) const
{
    return _mapFrame.getElevationLayerByName(name);
}

ElevationLayer* LayerManager::getElevationLayerAt(int index) const
{
    return _mapFrame.getElevationLayerAt(index);
}

void LayerManager::removetImageLayerByName(const std::string& name)
{
    if (_activeMap)
        _activeMap->removeImageLayer(getImageLayerByName(name));
}

void LayerManager::removetElevationLayerByName(const std::string& name)
{
    if (_activeMap)
        _activeMap->removeElevationLayer(getElevationLayerByName(name));
}

void LayerManager::addImageLayer(ImageLayer* layer)
{
    if (_activeMap)
        _activeMap->addImageLayer(layer);
}

void LayerManager::addElevationLayer(ElevationLayer* layer)
{
    if (_activeMap)
        _activeMap->addElevationLayer(layer);
}

void LayerManager::clearImageLayers()
{
    if (_activeMap) {
        ImageLayerVector imageLayersRemoved(imageLayers());
        for (ImageLayerVector::iterator i = imageLayersRemoved.begin(); i != imageLayersRemoved.end(); ++i)
            _activeMap->removeImageLayer(i->get());
    }
}

void LayerManager::clearElevationLayers()
{
    if (_activeMap) {
        ElevationLayerVector elevLayersRemoved;
        for (ElevationLayerVector::iterator i = elevLayersRemoved.begin(); i != elevLayersRemoved.end(); ++i)
            _activeMap->removeElevationLayer(i->get());
    }
}

// LayerManagerQtQml
LayerManagerQtQml::Index::Index(LayerManager* mgr)
    : osgQtQml::Index(mgr)
    , _completeInfo(0)
{
}

LayerManagerQtQml::Index::~Index()
{
    if (_completeInfo)
        delete _completeInfo;
}

void LayerManagerQtQml::Index::classBegin()
{
}

void LayerManagerQtQml::Index::componentComplete()
{
    if (!o(this) && mapNode) {
        setO(new LayerManager(mapNode));
    }
    osgQtQml::Index::componentComplete();
}

LayerManagerQtQml::LayerManagerQtQml(QObject* parent)
    : osgQtQml::Object(parent)
{
}

LayerManagerQtQml::LayerManagerQtQml(LayerManagerQtQml::Index* index, QObject* parent)
    : osgQtQml::Object(index, parent)
{
}

void LayerManagerQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

void LayerManagerQtQml::componentComplete()
{
    osgQtQml::Object::componentComplete();
    if (Index::CompleteInfo* info = i(this)->_completeInfo) {
        for (QList<ImageLayerQtQml*>::iterator it = info->imageLayers.begin(); it != info->imageLayers.end(); ++it) {
            addImageLayer(*it);
        }
        for (QList<ElevationLayerQtQml*>::iterator it = info->elevationLayers.begin(); it != info->elevationLayers.end(); ++it) {
            addElevationLayer(*it);
        }
    }
}

QQmlListProperty<ImageLayerQtQml> LayerManagerQtQml::imageLayers()
{
    return QQmlListProperty<ImageLayerQtQml>(this, (void*)0,
        LayerManagerQtQml::imageLayersAppend,
        LayerManagerQtQml::imageLayersCount,
        LayerManagerQtQml::imageLayersAt,
        LayerManagerQtQml::imageLayersClear);
}

QQmlListProperty<ElevationLayerQtQml> LayerManagerQtQml::elevationLayers()
{
    return QQmlListProperty<ElevationLayerQtQml>(this, (void*)0,
        LayerManagerQtQml::elevationLayersAppend,
        LayerManagerQtQml::elevationLayersCount,
        LayerManagerQtQml::elevationLayersAt,
        LayerManagerQtQml::elevationLayersClear);
}

int LayerManagerQtQml::getNumImagelayer()
{
    return o(this)->imageLayers().size();
}

int LayerManagerQtQml::getNumElevationLayer()
{
    return o(this)->elevationLayers().size();
}

ImageLayerQtQml* LayerManagerQtQml::getImageLayer(int index)
{
    return ImageLayerQtQml::fromImageLayer(o(this)->getImageLayerAt(index));
}

ElevationLayerQtQml* LayerManagerQtQml::getElevationLayer(int index)
{
    return ElevationLayerQtQml::fromElevationLayer(o(this)->getElevationLayerAt(index));
}

bool LayerManagerQtQml::addImageLayer(ImageLayerQtQml* layer)
{
    if (!isComplete()) {
        i(this)->info()->imageLayers.append(layer);
        return false;
    } else {
        o(this)->addImageLayer(layer->imageLayer());
        emit numImageLayersChanged(getNumImagelayer());
        return true;
    }
}

bool LayerManagerQtQml::addElevationLayer(ElevationLayerQtQml* layer)
{
    if (!isComplete()) {
        i(this)->info()->elevationLayers.append(layer);
        return false;
    } else {
        o(this)->addElevationLayer(layer->elevationLayer());
        emit numElevationLayersChanged(getNumElevationLayer());
        return true;
    }
}

void LayerManagerQtQml::clearImageLayers()
{
    o(this)->clearImageLayers();
    emit numImageLayersChanged(getNumImagelayer());
}

void LayerManagerQtQml::clearElevationLayers()
{
    o(this)->clearElevationLayers();
    emit numElevationLayersChanged(getNumElevationLayer());
}

QString LayerManagerQtQml::getImageLayerName(int index)
{
    return QString::fromStdString(o(this)->getImageLayerAt(index)->getName());
}

QString LayerManagerQtQml::getElevationLayerName(int index)
{
    return QString::fromStdString(o(this)->getElevationLayerAt(index)->getName());
}

void LayerManagerQtQml::setImageLayerVisible(int index, bool visible)
{
    o(this)->getImageLayerAt(index)->setVisible(visible);
}

void LayerManagerQtQml::setImageLayerVisibleByName(QString name, bool visible)
{
    o(this)->getImageLayerByName(name.toStdString())->setVisible(visible);
}

void LayerManagerQtQml::setElevationLayerVisible(int index, bool visible)
{
    o(this)->getElevationLayerAt(index)->setVisible(visible);
}

void LayerManagerQtQml::setElevationLayerVisibleByName(QString name, bool visible)
{
    o(this)->getElevationLayerByName(name.toStdString())->setVisible(visible);
}

MapNodeQtQml* LayerManagerQtQml::mapNode()
{
    return MapNodeQtQml::fromMapNode(i(this)->mapNode);
}

LayerManager* LayerManagerQtQml::layerManager()
{
    return o(this);
}

LayerManagerQtQml* LayerManagerQtQml::fromLayerManager(LayerManager* mgr, QObject* parent)
{
    if (!mgr)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(mgr)) {
        return static_cast<LayerManagerQtQml*>(index->qtObject());
    }

    LayerManagerQtQml* result = new LayerManagerQtQml(new Index(mgr), parent);
    result->classBegin();

    return result;
}

void LayerManagerQtQml::setMapNode(MapNodeQtQml* mapNode)
{
    i(this)->mapNode = mapNode->mapNode();
}

int LayerManagerQtQml::imageLayersCount(QQmlListProperty<ImageLayerQtQml>* list)
{
    return static_cast<LayerManagerQtQml*>(list->object)->getNumImagelayer();
}

ImageLayerQtQml* LayerManagerQtQml::imageLayersAt(QQmlListProperty<ImageLayerQtQml>* list, int index)
{
    return static_cast<LayerManagerQtQml*>(list->object)->getImageLayer(index);
}

void LayerManagerQtQml::imageLayersAppend(QQmlListProperty<ImageLayerQtQml>* list, ImageLayerQtQml* layer)
{
    static_cast<LayerManagerQtQml*>(list->object)->addImageLayer(layer);
}

void LayerManagerQtQml::imageLayersClear(QQmlListProperty<ImageLayerQtQml>* list)
{
    static_cast<LayerManagerQtQml*>(list->object)->clearImageLayers();
}

int LayerManagerQtQml::elevationLayersCount(QQmlListProperty<ElevationLayerQtQml>* list)
{
    return static_cast<LayerManagerQtQml*>(list->object)->getNumElevationLayer();
}

ElevationLayerQtQml* LayerManagerQtQml::elevationLayersAt(QQmlListProperty<ElevationLayerQtQml>* list, int index)
{
    return static_cast<LayerManagerQtQml*>(list->object)->getElevationLayer(index);
}

void LayerManagerQtQml::elevationLayersAppend(QQmlListProperty<ElevationLayerQtQml>* list, ElevationLayerQtQml* layer)
{
    static_cast<LayerManagerQtQml*>(list->object)->addElevationLayer(layer);
}

void LayerManagerQtQml::elevationLayersClear(QQmlListProperty<ElevationLayerQtQml>* list)
{
    static_cast<LayerManagerQtQml*>(list->object)->clearElevationLayers();
}
}
