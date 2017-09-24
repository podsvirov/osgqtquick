#ifndef _OSGEARTH_ANNO_ORTHO_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNO_ORTHO_NODE_QTQML_INDEX_

#include "geopositionnode.hpp"
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/AnnotationNodeQtQmlIndex>
#include <osgEarthAnnotation/GeoPositionNode>

namespace osgEarth {
namespace Annotation {
    class OSGQTQML_EXPORT GeoPositionNodeQtQml::Index : public AnnotationNodeQtQml::Index {
    public:
        typedef GeoPositionNode OType;
        typedef GeoPositionNodeQtQml QType;
        friend class GeoPositionNodeQtQml;

    public:
        Index(GeoPositionNode* o = 0);
        void classBegin();

        osgEarth::MapNode* mapNode;
        QGeoCoordinate position;
    };
}
}

#endif
