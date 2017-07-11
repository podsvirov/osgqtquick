#ifndef _OSGEARTH_ANNO_PLACE_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNO_PLACE_NODE_QTQML_INDEX_ 1

#include "placenode.hpp"
#include <osgEarthAnnotation/GeoPositionNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT PlaceNodeQtQml::Index : public GeoPositionNodeQtQml::Index {
    public:
        typedef PlaceNode OType;
        typedef PlaceNodeQtQml QType;
        friend class PlaceNodeQtQml;

    public:
        Index(PlaceNode* o = 0);
        void classBegin();
        void componentComplete();

        QString styleUrl;
        QColor styleHalo;
        QString text;
        osgEarth::Symbology::Style style;
    };
}
}

#endif // _OSGTEXT_STYLE_QTQML_INDEX_
