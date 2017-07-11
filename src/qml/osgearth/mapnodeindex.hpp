#ifndef _OSGEARTH_MAPNODE_QTQML_INDEX_
#define _OSGEARTH_MAPNODE_QTQML_INDEX_ 1

#include "mapnode.hpp"
#include <osg/GroupQtQmlIndex>

namespace osgEarth {
class OSGQTQML_EXPORT MapNodeQtQml::Index : public GroupQtQml::Index {
public:
    typedef MapNode OType;
    typedef MapNodeQtQml QType;
    friend class MapNodeQtQml;

public:
    Index(MapNode* o = 0);

    void classBegin();
    void componentComplete();

    osg::Node* graph;
};
}

#endif
