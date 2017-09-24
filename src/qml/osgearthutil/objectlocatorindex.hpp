#ifndef _OSGEARTH_UTIL_OBJECT_LOCATOR_QTQML_INDEX_
#define _OSGEARTH_UTIL_OBJECT_LOCATOR_QTQML_INDEX_ 1

#include "objectlocator.hpp"
#include <QGeoCoordinate>
#include <osg/MatrixTransformQtQmlIndex>
#include <osg/NodeQtQmlIndex>
#include <osgEarth/MapNode>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT ObjectLocatorNodeQtQml::Index : public osg::MatrixTransformQtQml::Index {
    public:
        typedef ObjectLocatorNode OType;
        typedef ObjectLocatorNodeQtQml QType;
        friend class ObjectLocatorNodeQtQml;
        Index(ObjectLocatorNode* o = 0);

    public:
        void classBegin();
        void componentComplete();

        osg::GroupQtQml* parent;
        osgEarth::MapNode* mapNode;
        QGeoCoordinate position;
        osg::NodeQtQml* object;
        QString url;
    };
}
}

#endif
