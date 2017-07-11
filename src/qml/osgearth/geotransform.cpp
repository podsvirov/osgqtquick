#include "geotransform.hpp"
#include "geotransformindex.hpp"

namespace osgEarth {

GeoTransformQtQml::Index::Index(GeoTransform* transform)
    : osg::MatrixTransformQtQml::Index(transform)
    , mapNode(0)
{
}

void GeoTransformQtQml::Index::classBegin()
{
    if (!o(this))
        setO(new GeoTransform);

    osg::MatrixTransformQtQml::Index::classBegin();
}

GeoTransformQtQml::GeoTransformQtQml(QObject* parent)
    : osg::MatrixTransformQtQml(parent)
{
}

GeoTransformQtQml::GeoTransformQtQml(GeoTransformQtQml::Index* index, QObject* parent)
    : osg::MatrixTransformQtQml(index, parent)
{
}

void GeoTransformQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    osg::MatrixTransformQtQml::classBegin();
}

void GeoTransformQtQml::componentComplete()
{
    osg::MatrixTransformQtQml::componentComplete();

    setPosition(i(this)->position);
}

osgEarth::MapNodeQtQml* GeoTransformQtQml::mapNode() const
{
    return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
}

QGeoCoordinate GeoTransformQtQml::position() const
{
    return i(this)->position;
}

GeoTransform* GeoTransformQtQml::geoTransform()
{
    return o(this);
}

GeoTransformQtQml* GeoTransformQtQml::fromGeoTransform(GeoTransform* transform, QObject* parent)
{
    if (!transform)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(transform)) {
        return static_cast<GeoTransformQtQml*>(index->qtObject());
    }

    return new GeoTransformQtQml(new Index(transform), parent);
}

void GeoTransformQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
{
    if (!isComplete()) {
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        return;
    }
    i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
    emit mapNodeChanged(mapNode);
}

void GeoTransformQtQml::setPosition(QGeoCoordinate position)
{
    if (!isComplete()) {
        i(this)->position = position;
        return;
    }

    if (osgQt::qGeoPoint(o(this)->getPosition()) == position)
        return;

    i(this)->position = position;

    if (auto _mapNode = i(this)->mapNode) {
        if (auto _geoSRS = _mapNode->getMapSRS()->getGeographicSRS()) {
            o(this)->setPosition(osgEarth::GeoPoint(_geoSRS, osgQt::vec3d(position), osgEarth::ALTMODE_ABSOLUTE));
        }
    }

    emit positionChanged(position);
}
}
