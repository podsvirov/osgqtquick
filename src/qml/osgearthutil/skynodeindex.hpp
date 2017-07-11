#ifndef _OSGEARTHUTIL_SKY_NODE_QTQML_INDEX_
#define _OSGEARTHUTIL_SKY_NODE_QTQML_INDEX_ 1

#include "skynode.hpp"
#include <osg/GroupQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT SkyNodeQtQml::Index : public osg::GroupQtQml::Index {
    public:
        typedef SkyNode OType;
        typedef SkyNodeQtQml QType;
        friend class SkyNodeQtQml;
        Index(SkyNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

        osgEarth::MapNode* mapNode;

        bool sunVisible;
        bool moonVisible;
        bool starsVisible;
        bool atmosphereVisible;
        int lighting;
    };
}
}

#endif
