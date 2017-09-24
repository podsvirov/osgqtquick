
#ifndef _OSGEARTHUTIL_VERTICAL_SCALE_QTQML_INDEX_
#define _OSGEARTHUTIL_VERTICAL_SCALE_QTQML_INDEX_ 1

#include "verticalscale.hpp"
#include <osgEarth/TerrainEffectQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT VerticalScaleQtQml::Index : public osgEarth::TerrainEffectQtQml::Index {
    public:
        typedef VerticalScale OType;
        typedef VerticalScaleQtQml QType;
        friend class VerticalScaleQtQml;

    public:
        Index(VerticalScale* o = 0);
        void classBegin();

    public:
        float scale;
    };
}
}

#endif
