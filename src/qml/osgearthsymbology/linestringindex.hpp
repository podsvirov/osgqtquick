
#ifndef _OSGEARTH_SYMBOLOGY_LINE_STRING_QTQML_INDEX_
#define _OSGEARTH_SYMBOLOGY_LINE_STRING_QTQML_INDEX_ 1

#include "linestring.hpp"
#include <osgEarthAnnotation/AnnotationNodeQtQmlIndex>
#include <osgEarthAnnotation/FeatureNode>

namespace osgEarth {
namespace Symbology {
    class OSGQTQML_EXPORT LineStringQtQml::Index : public osgEarth::Annotation::AnnotationNodeQtQml::Index {
    public:
        typedef osgEarth::Annotation::FeatureNode OType;
        typedef LineStringQtQml QType;
        friend class LineStringQtQml;

    public:
        Index(osgEarth::Annotation::FeatureNode* o = 0);
    };
}
} // osgEarth::Symbology

#endif
