#ifndef _OSGEARTH_ANNO_LABEL_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNO_LABEL_NODE_QTQML_INDEX_ 1

#include "labelnode.hpp"
#include <osgEarthAnnotation/GeoPositionNodeQtQmlIndex>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT LabelNodeQtQml::Index : public GeoPositionNodeQtQml::Index {
    public:
        typedef LabelNode OType;
        typedef LabelNodeQtQml QType;
        friend class LabelNodeQtQml;
        Index(LabelNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

    public:
        osgEarth::Symbology::Style style;
        QColor styleColor;
        QString text;
    };
}
}

#endif
