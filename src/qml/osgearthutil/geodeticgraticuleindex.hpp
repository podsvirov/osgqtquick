#ifndef _OSGEARTHUTIL_GEODETICGRATICULE_QTQML_INDEX_
#define _OSGEARTHUTIL_GEODETICGRATICULE_QTQML_INDEX_ 1

#include "geodeticgraticule.hpp"
#include <osg/GroupQtQmlIndex>
#include <osgEarth/MapNode>

namespace osgEarth {
namespace Util {
    class GeodeticGraticuleQtQml::Index : public osg::GroupQtQml::Index {
    public:
        typedef GraticuleNode OType;
        typedef GeodeticGraticuleQtQml QType;
        friend class GeodeticGraticuleQtQml;

    public:
        Index(GraticuleNode* o = 0);
        void classBegin();
        void componentComplete();

        osgEarth::MapNode* mapNode;
        osg::Group* parent;
        QColor color;
        bool visible;
    };
}
}

#endif
