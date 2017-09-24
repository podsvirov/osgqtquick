#ifndef _OSGEARTHUTIL_CONTOUR_MAP_QTQML_INDEX_
#define _OSGEARTHUTIL_CONTOUR_MAP_QTQML_INDEX_ 1
#include "contourmap.hpp"
#include <osgEarth/TerrainEffectQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT ContourMapQtQml::Index : public osgEarth::TerrainEffectQtQml::Index {
    public:
        typedef ContourMap OType;
        typedef ContourMapQtQml QType;
        friend class ContourMapQtQml;

    public:
        Index(ContourMap* o = 0);
        void classBegin();

    public:
        float opacity;
        bool grayscale;
    };
}
}

#endif
