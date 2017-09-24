#ifndef _OSGEARTHUTIL_OCEAN_NODE_QTQML_INDEX_
#define _OSGEARTHUTIL_OCEAN_NODE_QTQML_INDEX_ 1

#include "oceannode.hpp"
#include <osg/GroupQtQmlIndex>
#include <osgEarth/MapNode>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT OceanNodeQtQml::Index : public osg::GroupQtQml::Index {
    public:
        typedef OceanNode OType;
        typedef OceanNodeQtQml QType;
        friend class OceanNodeQtQml;
        Index(OceanNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

        osgEarth::MapNode* mapNode;
        float seaLevel;
        float alpha;
    };
}
}

#endif
