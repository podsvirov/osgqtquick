#include "geopositionnode.hpp"
#include "geopositionnodeindex.hpp"

namespace osgEarth {
namespace Annotation {

    GeoPositionNodeQtQml::Index::Index(GeoPositionNode* node)
        : AnnotationNodeQtQml::Index(node)
        , mapNode(0)
    {
    }

    GeoPositionNodeQtQml::GeoPositionNodeQtQml(QObject* parent)
        : AnnotationNodeQtQml(parent)
    {
    }

    void GeoPositionNodeQtQml::Index::classBegin()
    {
        if (!o(this))
            setO(new GeoPositionNode);

        AnnotationNodeQtQml::Index::classBegin();
    }

    GeoPositionNodeQtQml::GeoPositionNodeQtQml(GeoPositionNodeQtQml::Index* index, QObject* parent)
        : AnnotationNodeQtQml(index, parent)
    {
    }

    void GeoPositionNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        AnnotationNodeQtQml::classBegin();
    }

    GeoTransformQtQml* GeoPositionNodeQtQml::geoTransform()
    {
        GeoTransform* transform = o(this)->getGeoTransform();
        return GeoTransformQtQml::fromGeoTransform(transform, this);
    }

    QGeoCoordinate GeoPositionNodeQtQml::position() const
    {
        return i(this)->position;
    }

    osgEarth::MapNodeQtQml* GeoPositionNodeQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    void GeoPositionNodeQtQml::setPosition(QGeoCoordinate position)
    {

        if (!isComplete()) {
            i(this)->position = position;
            return;
        }

        //        if (osgQt::qGeoPoint(o(this)->getPosition()) == position)
        //            return;

        i(this)->position = position;

        if (auto _mapNode = i(this)->mapNode) {
            if (auto _geoSRS = _mapNode->getMapSRS()->getGeographicSRS()) {
                o(this)->setPosition(osgEarth::GeoPoint(_geoSRS, osgQt::vec3d(position), osgEarth::ALTMODE_ABSOLUTE));
            }
        }
    }

    void GeoPositionNodeQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        emit mapNodeChanged(mapNode);
    }
}
}
