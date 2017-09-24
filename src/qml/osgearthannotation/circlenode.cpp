
#include "circlenode.hpp"
#include "circlenodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthSymbology/Style>

namespace osgEarth {
namespace Annotation {

    CircleNodeQtQml::Index::Index(CircleNode* o)
        : GeoPositionNodeQtQml::Index(o)
        , styleColor(QColor::fromRgba(qRgba(255, 0, 0, 0.5)))
        , radius(1.0)
        , arcStart(0.0)
        , arcEnd(0.0)
    {
    }

    void CircleNodeQtQml::Index::classBegin()
    {
        //  GeoPositionNodeQtQml::Index::classBegin();
    }

    void CircleNodeQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            style.getOrCreate<PolygonSymbol>()->fill()->color() = osgQt::swapColor(styleColor);
            style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
            const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
            GeoPoint point = GeoPoint(geoSRS, osgQt::vec3d(position), ALTMODE_RELATIVE);
            CircleNode* circleNode = new osgEarth::Annotation::CircleNode(mapNode, point, Distance(radius, Units::KILOMETERS), style, Angle(arcStart, Units::DEGREES), Angle(arcEnd, Units::DEGREES), true);

            setO(circleNode);
        }
        GeoPositionNodeQtQml::Index::componentComplete();
    }

    CircleNodeQtQml::CircleNodeQtQml(QObject* parent)
        : GeoPositionNodeQtQml(parent)
    {
    }

    CircleNodeQtQml::CircleNodeQtQml(CircleNodeQtQml::Index* index, QObject* parent)
        : GeoPositionNodeQtQml(index, parent)
    {
    }

    void CircleNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        GeoPositionNodeQtQml::classBegin();
    }

    QColor CircleNodeQtQml::styleColor() const
    {
        return i(this)->styleColor;
    }

    double CircleNodeQtQml::radius() const
    {
        return i(this)->radius;
    }

    double CircleNodeQtQml::arcStart() const
    {
        return i(this)->arcStart;
    }

    double CircleNodeQtQml::arcEnd() const
    {
        return i(this)->arcEnd;
    }

    void CircleNodeQtQml::setStyleColor(QColor styleColor)
    {
        if (!isComplete()) {
            i(this)->styleColor = styleColor;
            return;
        }

        i(this)->styleColor = styleColor;

        emit styleColorChanged(styleColor);
    }

    void CircleNodeQtQml::setRadius(double radius)
    {
        if (!isComplete()) {
            i(this)->radius = radius;
            return;
        }

        i(this)->radius = radius;

        emit radiusChanged(radius);
    }

    void CircleNodeQtQml::setArcStart(double arcStart)
    {
        if (!isComplete()) {
            i(this)->arcStart = arcStart;
            return;
        }

        i(this)->arcStart = arcStart;

        emit arcStartChanged(arcStart);
    }

    void CircleNodeQtQml::setArcEnd(double arcEnd)
    {
        if (!isComplete()) {
            i(this)->arcEnd = arcEnd;
            return;
        }

        i(this)->arcEnd = arcEnd;

        emit arcEndChanged(arcEnd);
    }
}
}
