#ifndef OSGEARTH_ANNOTATION_RECTANGLE_QTQTML_INDEX_
#define OSGEARTH_ANNOTATION_RECTANGLE_QTQTML_INDEX_ 1

#include "rectanglenode.hpp"
#include <osgEarthAnnotation/GeoPositionNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {
    class OSGQTQML_EXPORT RectangleNodeQtQml::Index : public GeoPositionNodeQtQml::Index {
    public:
        typedef RectangleNode OType;
        typedef RectangleNodeQtQml QType;
        friend class RectangleNodeQtQml;

        Index(RectangleNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

    public:
        double width;
        double height;
        QColor fillColor;
        osgEarth::Symbology::Style style;
    };
}
}
#endif
