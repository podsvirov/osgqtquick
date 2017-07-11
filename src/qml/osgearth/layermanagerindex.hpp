#ifndef _OSGEARTH_LAYER_MANAGER_QTQML_INDEX_
#define _OSGEARTH_LAYER_MANAGER_QTQML_INDEX_ 1

#include "layermanager.hpp"
#include <osg/ObjectQtQmlIndex>

namespace osgEarth {

// LayerManagerQtQml::Index
class OSGQTQML_EXPORT LayerManagerQtQml::Index : public osgQtQml::Index {
public:
    typedef LayerManager OType;
    typedef LayerManagerQtQml QType;
    friend class LayerManagerQtQml;

public:
    Index(LayerManager* o = 0);
    ~Index();

    void classBegin();
    void componentComplete();

protected:
    struct CompleteInfo;
    CompleteInfo* _completeInfo;
    CompleteInfo* info();

private:
    MapNode* mapNode;
};

struct LayerManagerQtQml::Index::CompleteInfo {
    QList<ImageLayerQtQml*> imageLayers;
    QList<ElevationLayerQtQml*> elevationLayers;
};

inline LayerManagerQtQml::Index::CompleteInfo* LayerManagerQtQml::Index::info()
{
    return _completeInfo ? _completeInfo : _completeInfo = new CompleteInfo;
}
}

#endif
