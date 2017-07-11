#include "linestring.hpp"
#include "linestringindex.hpp"

#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/Geometry>

namespace osgEarth {
namespace Annotation {

    LineStringQtQml::Index::Index(FeatureNode* node)
        : AnnotationNodeQtQml::Index(node)
    {
    }

    void LineStringQtQml::Index::classBegin()
    {
    }

    void LineStringQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            osgEarth::Symbology::Geometry* path = new osgEarth::Symbology::LineString();
            path->push_back(osg::Vec3d(osgQt::vec3d(start)));
            path->push_back(osg::Vec3d(osgQt::vec3d(end)));
            const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
            osgEarth::Features::Feature* feature = new osgEarth::Features::Feature(path, geoSRS);
            feature->geoInterp() = osgEarth::GEOINTERP_GREAT_CIRCLE;
            style.getOrCreate<LineSymbol>()->stroke()->color() = Color::White;
            style.getOrCreate<LineSymbol>()->stroke()->width() = 1.0f;
            style.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
            style.getOrCreate<PointSymbol>()->size() = 5;
            style.getOrCreate<PointSymbol>()->fill()->color() = Color::Red;
            style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
            //pathStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
            osgEarth::Annotation::FeatureNode* pathNode = new osgEarth::Annotation::FeatureNode(mapNode, feature, style);
            setO(pathNode);
        }
        AnnotationNodeQtQml::Index::componentComplete();
    }

    LineStringQtQml::LineStringQtQml(QObject* parent)
        : AnnotationNodeQtQml(parent)
    {
    }

    LineStringQtQml::LineStringQtQml(Index* index, QObject* parent)
        : AnnotationNodeQtQml(index, parent)
    {
    }

    void LineStringQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        AnnotationNodeQtQml::classBegin();
    }

    QVector3D LineStringQtQml::start() const
    {
        return i(this)->start;
    }

    QVector3D LineStringQtQml::end() const
    {
        return i(this)->end;
    }

    QColor LineStringQtQml::lineColor() const
    {
        return i(this)->lineColor;
    }

    double LineStringQtQml::lineWidth() const
    {
        return i(this)->lineWidth;
    }

    double LineStringQtQml::pointSize() const
    {
        return i(this)->pointSize;
    }

    QColor LineStringQtQml::pointColor() const
    {
        return i(this)->pointColor;
    }

    osgEarth::MapNodeQtQml* LineStringQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    void LineStringQtQml::setStart(QVector3D start)
    {
        if (!isComplete()) {
            i(this)->start = start;
        }

        i(this)->start = start;

        emit startChanged(start);
    }

    void LineStringQtQml::setEnd(QVector3D end)
    {
        if (!isComplete()) {
            i(this)->end = end;
            return;
        }

        i(this)->end = end;

        emit endChanged(end);
    }

    void LineStringQtQml::setLineColor(QColor lineColor)
    {
        if (!isComplete()) {
            i(this)->lineColor = lineColor;
            return;
        }

        i(this)->lineColor = lineColor;

        emit lineColorChanged(lineColor);
    }

    void LineStringQtQml::setLineWidth(double lineWidth)
    {
        if (!isComplete()) {
            i(this)->lineWidth = lineWidth;
            return;
        }

        i(this)->lineWidth = lineWidth;

        emit lineWidthChanged(lineWidth);
    }

    void LineStringQtQml::setPointSize(double pointSize)
    {
        if (!isComplete()) {
            i(this)->pointSize = pointSize;
            return;
        }

        i(this)->pointSize = pointSize;
        emit pointSizeChanged(pointSize);
    }

    void LineStringQtQml::setPointColor(QColor pointColor)
    {
        if (!isComplete()) {
            i(this)->pointColor = pointColor;
            return;
        }

        i(this)->pointColor = pointColor;

        emit pointColorChanged(pointColor);
    }

    void LineStringQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
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
