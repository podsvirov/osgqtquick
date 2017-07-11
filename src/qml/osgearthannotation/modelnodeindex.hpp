#ifndef _OSGEARTH_ANNO_MODEL_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNO_MODEL_NODE_QTQML_INDEX_ 1

#include "modelnode.hpp"
#include <osg/NodeQtQmlIndex>
#include <osgEarthAnnotation/GeoPositionNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {
    class OSGQTQML_EXPORT ModelNodeQtQml::Index : public GeoPositionNodeQtQml::Index {
    public:
        typedef ModelNode OType;
        typedef ModelNodeQtQml QType;
        friend class ModelNodeQtQml;
        Index(ModelNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

        QString url;
        QString label;
        osgEarth::Symbology::Style style;
    };
}
} // namespace osgEarth::Annotation

#endif // _OSGEARTH_ANNO_MODEL_NODE_QTQML_INDEX_
