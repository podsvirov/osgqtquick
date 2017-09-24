

#ifndef _OSGEARTH_ANNO_CIRCLE_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNO_CIRCLE_NODE_QTQML_INDEX_ 1

#include "circlenode.hpp"
#include <osgEarthAnnotation/GeoPositionNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT CircleNodeQtQml::Index : public GeoPositionNodeQtQml::Index {
    public:
        typedef CircleNode OType;
        typedef CircleNodeQtQml QType;
        friend class CircleNodeQtQml;

        Index(CircleNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

    public:
        double arcEnd;
        QColor styleColor;
        double radius;
        double arcStart;

        osgEarth::Symbology::Style style;
    };
}
} // namespace osgEarth::Annotation

#endif
