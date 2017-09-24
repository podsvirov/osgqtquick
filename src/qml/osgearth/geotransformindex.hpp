#ifndef _OSGEARTH_GEOTRANSFORM_QTQML_INDEX_
#define _OSGEARTH_GEOTRANSFORM_QTQML_INDEX_ 1

#include "geotransform.hpp"
#include <osg/MatrixTransformQtQmlIndex>
#include <osgEarth/GeoMath>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osgEarth/Utils>

namespace osgEarth {
class GeoTransform;
class OSGQTQML_EXPORT GeoTransformQtQml::Index : public osg::MatrixTransformQtQml::Index {
public:
    typedef GeoTransform OType;
    typedef GeoTransformQtQml QType;
    friend class GeoTransformQtQml;

public:
    Index(GeoTransform* o = 0);

    void classBegin();

    osgEarth::MapNode* mapNode;
    QGeoCoordinate position;
};
}

#endif
