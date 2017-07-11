#ifndef _OSGEARTH_ANNO_IMAGE_OVERLAY_QTQML_INDEX_
#define _OSGEARTH_ANNO_IMAGE_OVERLAY_QTQML_INDEX_ 1

#include "imageoverlay.hpp"
#include <osgEarthAnnotation/AnnotationNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {
    class OSGQTQML_EXPORT ImageOverlayQtQml::Index : public AnnotationNodeQtQml::Index {
    public:
        typedef ImageOverlay OType;
        typedef ImageOverlayQtQml QType;
        friend class ImageOverlayQtQml;

        Index(ImageOverlay* o = 0);

    public:
        void classBegin();
        void componentComplete();

    public:
        osgEarth::MapNode* mapNode;
        QString filename;
        QVector4D bounds;
    };
}
} // namespace osgEarth::Annotation

#endif
