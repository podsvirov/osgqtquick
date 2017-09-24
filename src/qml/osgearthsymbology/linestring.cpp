#include "linestring.hpp"
#include "linestringindex.hpp"
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/Geometry>

namespace osgEarth {
namespace Symbology {

    LineStringQtQml::Index::Index(osgEarth::Annotation::FeatureNode* node)
        : osgEarth::Annotation::AnnotationNodeQtQml::Index(node)
    {
    }

    LineStringQtQml::LineStringQtQml(QObject* parent)
        : osgEarth::Annotation::AnnotationNodeQtQml(parent)
    {
    }

    LineStringQtQml::LineStringQtQml(Annotation::AnnotationNodeQtQml::Index* index, QObject* parent)
        : osgEarth::Annotation::AnnotationNodeQtQml(index, parent)
    {
    }

    void LineStringQtQml::classBegin()
    {
        osgEarth::Annotation::AnnotationNodeQtQml::classBegin();
    }

    void LineStringQtQml::componentComplete()
    {
        osgEarth::Symbology::Geometry* path = new osgEarth::Symbology::LineString();
        path->push_back(osg::Vec3d(m_start.x(), m_start.y(), m_start.z()));
        path->push_back(osg::Vec3d(m_end.x(), m_end.y(), m_end.z()));

        MapNode* mapNode = MapNode::findMapNode(m_mapNode->group());
        const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();

        osgEarth::Features::Feature* pathFeature = new osgEarth::Features::Feature(path, geoSRS);
        pathFeature->geoInterp() = osgEarth::GEOINTERP_GREAT_CIRCLE;

        osgEarth::Symbology::Style pathStyle;
        pathStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::White;
        pathStyle.getOrCreate<LineSymbol>()->stroke()->width() = 1.0f;
        pathStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
        pathStyle.getOrCreate<PointSymbol>()->size() = 5;
        pathStyle.getOrCreate<PointSymbol>()->fill()->color() = Color::Red;
        pathStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
        //        pathStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

        osgEarth::Annotation::FeatureNode* pathNode = new osgEarth::Annotation::FeatureNode(mapNode, pathFeature, pathStyle);
        //        m_parent->group()->addChild(pathNode);
        setI(new Index(pathNode));
        i(this)->setQ(this);
        i(this)->setO(pathNode);
    }

    QVector3D LineStringQtQml::start() const
    {
        return m_start;
    }

    QVector3D LineStringQtQml::end() const
    {
        return m_end;
    }

    QColor LineStringQtQml::lineColor() const
    {
        return m_lineColor;
    }

    double LineStringQtQml::lineWidth() const
    {
        return m_lineWidth;
    }

    double LineStringQtQml::pointSize() const
    {
        return m_pointSize;
    }

    QColor LineStringQtQml::pointColor() const
    {
        return m_pointColor;
    }

    osg::GroupQtQml* LineStringQtQml::parent() const
    {
        return m_parent;
    }

    osg::GroupQtQml* LineStringQtQml::mapNode() const
    {
        return m_mapNode;
    }

    void LineStringQtQml::setStart(QVector3D start)
    {
        if (m_start == start)
            return;

        m_start = start;
        emit startChanged(start);
    }

    void LineStringQtQml::setEnd(QVector3D end)
    {
        if (m_end == end)
            return;

        m_end = end;
        emit endChanged(end);
    }

    void LineStringQtQml::setLineColor(QColor line_color)
    {
        if (m_lineColor == line_color)
            return;

        m_lineColor = line_color;
        emit lineColorChanged(line_color);
    }

    void LineStringQtQml::setLineWidth(double lineWidth)
    {
        if (m_lineWidth == lineWidth)
            return;

        m_lineWidth = lineWidth;
        emit lineWidthChanged(lineWidth);
    }

    void LineStringQtQml::setPointSize(double pointSize)
    {
        if (m_pointSize == pointSize)
            return;

        m_pointSize = pointSize;
        emit pointSizeChanged(pointSize);
    }

    void LineStringQtQml::setPointColor(QColor pointColor)
    {
        if (m_pointColor == pointColor)
            return;

        m_pointColor = pointColor;
        emit pointColorChanged(pointColor);
    }

    void LineStringQtQml::setParent(osg::GroupQtQml* parent)
    {
        if (m_parent == parent)
            return;

        m_parent = parent;
        emit parentChanged(parent);
    }

    void LineStringQtQml::setMapNode(osg::GroupQtQml* mapNode)
    {
        if (m_mapNode == mapNode)
            return;

        m_mapNode = mapNode;
        emit mapNodeChanged(mapNode);
    }
}
}
