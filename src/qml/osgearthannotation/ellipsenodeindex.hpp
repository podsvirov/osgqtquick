#ifndef _OSGEARTH_ANNOTATION_ELLIPSE_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNOTATION_ELLIPSE_NODE_QTQML_INDEX_ 1

#include "ellipsenode.hpp"
#include <osgEarthAnnotation/GeoPositionNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT EllipseNodeQtQml::Index : public GeoPositionNodeQtQml::Index {
    public:
        typedef EllipseNode OType;
        typedef EllipseNodeQtQml QType;
        friend class EllipseNodeQtQml;
        Index(EllipseNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

    public:
        QColor styleColor;
        double radiusMajor;
        double arcStart;
        double arcEnd;
        double radiusMinor;
        double rotationAngle;
        double height;
        osgEarth::Symbology::Style style;
    };
}
} // namespace osgEarth::Annotation

#endif
