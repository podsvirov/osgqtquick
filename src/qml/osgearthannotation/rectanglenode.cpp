#include "rectanglenode.hpp"
#include "rectanglenodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthSymbology/Style>

namespace osgEarth {
namespace Annotation {

    RectangleNodeQtQml::Index::Index(RectangleNode* o)
        : GeoPositionNodeQtQml::Index(o)
        , fillColor(Qt::green)
    {
    }

    void RectangleNodeQtQml::Index::classBegin()
    {
    }

    void RectangleNodeQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            style.getOrCreate<PolygonSymbol>()->fill()->color() = osgQt::swapColor(fillColor);
            const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
            RectangleNode* rectNode = new RectangleNode(mapNode,
                GeoPoint(geoSRS, osgQt::vec3d(position)), Distance(width, Units::KILOMETERS), Distance(height, Units::KILOMETERS), style);
            setO(rectNode);
        }
        GeoPositionNodeQtQml::Index::componentComplete();
    }

    RectangleNodeQtQml::RectangleNodeQtQml(QObject* parent)
        : GeoPositionNodeQtQml(parent)
    {
    }

    RectangleNodeQtQml::RectangleNodeQtQml(RectangleNodeQtQml::Index* index, QObject* parent)
        : GeoPositionNodeQtQml(index, parent)
    {
    }

    void RectangleNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        GeoPositionNodeQtQml::classBegin();
    }

    double RectangleNodeQtQml::width() const
    {
        return i(this)->width;
    }

    double RectangleNodeQtQml::height() const
    {
        return i(this)->height;
    }

    QColor RectangleNodeQtQml::fillColor() const
    {
        return i(this)->fillColor;
    }

    void RectangleNodeQtQml::setWidth(double width)
    {
        if (!isComplete()) {
            i(this)->width = width;
            return;
        }

        i(this)->width = width;

        emit widthChanged(width);
    }

    void RectangleNodeQtQml::setHeight(double height)
    {
        if (!isComplete()) {
            i(this)->height = height;
            return;
        }

        i(this)->height = height;

        emit heightChanged(height);
    }

    void RectangleNodeQtQml::setFillColor(QColor fillcolor)
    {
        if (!isComplete()) {
            i(this)->fillColor = fillcolor;
            return;
        }

        i(this)->fillColor = fillcolor;

        emit fillColorChanged(fillcolor);
    }
}
}
