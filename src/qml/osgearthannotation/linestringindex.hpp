
#ifndef _OSGEARTH_SYMBOLOGY_LINE_STRING_QTQML_INDEX_
#define _OSGEARTH_SYMBOLOGY_LINE_STRING_QTQML_INDEX_ 1

#include "linestring.hpp"
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/AnnotationNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {
    class OSGQTQML_EXPORT LineStringQtQml::Index : public AnnotationNodeQtQml::Index {
    public:
        typedef FeatureNode OType;
        typedef LineStringQtQml QType;
        friend class LineStringQtQml;

    public:
        Index(FeatureNode* o = 0);

        void classBegin();
        void componentComplete();

    public:
        QVector3D start;
        QVector3D end;
        QColor lineColor;
        double lineWidth;
        double pointSize;
        QColor pointColor;

        osgEarth::Symbology::Style style;
        osgEarth::MapNode* mapNode;
    };
}
} // osgEarth::Symbology

#endif
