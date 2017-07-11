#include "ellipsenode.hpp"
#include "ellipsenodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthSymbology/Style>

namespace osgEarth {
namespace Annotation {

    EllipseNodeQtQml::Index::Index(EllipseNode* o)
        : GeoPositionNodeQtQml::Index(o)
        , styleColor(Qt::blue)
        , rotationAngle(0)
        , height(250000.0)
    {
    }

    void EllipseNodeQtQml::Index::classBegin()
    {
    }

    void EllipseNodeQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            style.getOrCreate<PolygonSymbol>()->fill()->color() = osgQt::swapColor(styleColor);
            style.getOrCreate<ExtrusionSymbol>()->height() = height; // meters MSL
            const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
            GeoPoint point = GeoPoint(geoSRS, osgQt::vec3d(position), ALTMODE_RELATIVE);
            EllipseNode* ellipseNode = new EllipseNode(mapNode, point,
                Distance(radiusMajor, Units::MILES), Distance(radiusMinor, Units::MILES),
                Angle(rotationAngle, Units::DEGREES), style,
                Angle(arcStart, Units::DEGREES), Angle(arcEnd, Units::DEGREES), true);
            setO(ellipseNode);
        }
        GeoPositionNodeQtQml::Index::componentComplete();
    }

    EllipseNodeQtQml::EllipseNodeQtQml(QObject* parent)
        : GeoPositionNodeQtQml(parent)
    {
    }

    EllipseNodeQtQml::EllipseNodeQtQml(EllipseNodeQtQml::Index* /*index*/, QObject* /*parent*/)
    {
    }

    void EllipseNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        GeoPositionNodeQtQml::classBegin();
    }

    double EllipseNodeQtQml::height() const
    {
        return i(this)->height;
    }

    QColor EllipseNodeQtQml::styleColor() const
    {
        return i(this)->styleColor;
    }

    double EllipseNodeQtQml::radiusMajor() const
    {
        return i(this)->radiusMajor;
    }

    double EllipseNodeQtQml::arcStart() const
    {
        return i(this)->arcStart;
    }

    double EllipseNodeQtQml::arcEnd() const
    {
        return i(this)->arcEnd;
    }

    double EllipseNodeQtQml::radiusMinor() const
    {
        return i(this)->radiusMinor;
    }

    double EllipseNodeQtQml::rotationAngle() const
    {
        return i(this)->rotationAngle;
    }

    void EllipseNodeQtQml::setStyleColor(QColor styleColor)
    {
        if (!isComplete()) {
            i(this)->styleColor = styleColor;
            return;
        }

        i(this)->styleColor = styleColor;
        emit styleColorChanged(styleColor);
    }

    void EllipseNodeQtQml::setRadiusMajor(double radius)
    {
        if (!isComplete()) {
            i(this)->radiusMajor = radius;
            return;
        }

        i(this)->radiusMajor = radius;
        emit radiusMajorChanged(radius);
    }

    void EllipseNodeQtQml::setArcStart(double arcStart)
    {
        if (!isComplete()) {
            i(this)->arcStart = arcStart;
            return;
        }

        i(this)->arcStart = arcStart;
        emit arcStartChanged(arcStart);
    }

    void EllipseNodeQtQml::setArcEnd(double arcEnd)
    {
        if (!isComplete()) {
            i(this)->arcEnd = arcEnd;
            return;
        }

        i(this)->arcEnd = arcEnd;
        emit arcEndChanged(arcEnd);
    }

    void EllipseNodeQtQml::setRadiusMinor(double radiusMinor)
    {
        if (!isComplete()) {
            i(this)->radiusMinor = radiusMinor;
            return;
        }

        i(this)->radiusMinor = radiusMinor;
        emit radiusMinorChanged(radiusMinor);
    }

    void EllipseNodeQtQml::setRotationAngle(double rotationAngle)
    {
        if (!isComplete()) {
            i(this)->rotationAngle = rotationAngle;
            return;
        }

        i(this)->rotationAngle = rotationAngle;
        emit rotationAngleChanged(rotationAngle);
    }

    void EllipseNodeQtQml::setHeight(double height)
    {
        if (!isComplete()) {
            i(this)->height = height;
            return;
        }

        i(this)->height = height;
        emit heightChanged(height);
    }
}
}
