#include "terrainprofileanalysistool.hpp"
#include "terrainprofileanalysistoolindex.hpp"
#include <osgEarth/Registry>

namespace osgEarth {
namespace Util {
    TerrainProfileAnalysisTool::TerrainProfileAnalysisTool(TerrainProfileAnalysisToolQtQml* tpatQtQml, osgEarth::MapNode* mapNode, osg::Group* root, TerrainProfileCalculator* profileCalculator)
        : toolQml(tpatQtQml)
        , mapNode(mapNode)
        , root(root)
        , startValid(false)
        , profileCalculator(profileCalculator)
    {
        start = profileCalculator->getStart().vec3d();
        end = profileCalculator->getEnd().vec3d();
        compute();
    }

    bool TerrainProfileAnalysisTool::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
    {
        if (ea.getEventType() == ea.PUSH && ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
            osg::Vec3d world;
            if (mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world)) {
                GeoPoint mapPoint;
                mapPoint.fromWorld(mapNode->getMapSRS(), world);
                //_mapNode->getMap()->worldPointToMapPoint( world, mapPoint );

                if (!startValid) {
                    startValid = true;
                    start = mapPoint.vec3d();
                    if (featureNode.valid()) {
                        root->removeChild(featureNode.get());
                        featureNode = 0;
                    }
                } else {
                    end = mapPoint.vec3d();
                    compute();
                    startValid = false;
                }
            }
        }
        return false;
    }

    void TerrainProfileAnalysisTool::compute()
    {
        //Tell the calculator about the new start/end points
        profileCalculator->setStartEnd(GeoPoint(mapNode->getMapSRS(), start.x(), start.y()),
            GeoPoint(mapNode->getMapSRS(), end.x(), end.y()));

        if (featureNode.valid()) {
            root->removeChild(featureNode.get());
            featureNode = 0;
        }

        LineString* line = new LineString();
        line->push_back(start);
        line->push_back(end);
        osgEarth::Features::Feature* feature = new osgEarth::Features::Feature(line, mapNode->getMapSRS());
        feature->geoInterp() = GEOINTERP_GREAT_CIRCLE;

        //Define a style for the line
        Style style;
        LineSymbol* ls = style.getOrCreateSymbol<LineSymbol>();
        ls->stroke()->color() = Color::Yellow;
        ls->stroke()->width() = 2.0f;
        ls->tessellation() = 20;

        style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
        style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_SCENE;

        feature->style() = style;

        featureNode = new osgEarth::Annotation::FeatureNode(mapNode, feature);
        //Disable lighting
        featureNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        root->addChild(featureNode.get());

        // TODO

        const TerrainProfile& profile = profileCalculator->getProfile();
        (toolQml)->clearProfilePoints();

        double minElevation, maxElevation;
        profile.getElevationRanges(minElevation, maxElevation);
        double elevationRange = maxElevation - minElevation;
        double totalDistance = profile.getTotalDistance();

        (toolQml)->setMinElevation(minElevation);
        (toolQml)->setMaxElevation(maxElevation);
        (toolQml)->setTotalDistance(totalDistance);

        for (unsigned int i = 0; i < profile.getNumElevations(); i++) {
            double distance = profile.getDistance(i);
            double elevation = profile.getElevation(i);
            toolQml->addProfilePoint(distance, elevation);
            //            (toolQml)->i(toolQml)->profile.append(QVariant(QPointF(static_cast<float>(distance), static_cast<float>(elevation))));
            //            double x = (distance / totalDistance) * _graphWidth;
            //            double y = ((elevation - minElevation) / elevationRange) * _graphHeight;
            //            verts->push_back(osg::Vec3(x, y, 0));
        }
        emit toolQml->profileChanged();
    }

    TerrainProfileAnalysisToolQtQml::Index::Index(TerrainProfileAnalysisTool* tool)
        : osgGA::GUIEventHandlerQtQml::Index(tool)
        , minElevation(0)
        , maxElevation(0)
        , totalDistance(0)
    {
    }

    void TerrainProfileAnalysisToolQtQml::Index::classBegin()
    {
    }

    void TerrainProfileAnalysisToolQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            osg::ref_ptr<TerrainProfileCalculator> calculator = new TerrainProfileCalculator(mapNode);
            TerrainProfileAnalysisTool* tpat = new TerrainProfileAnalysisTool(q(this), mapNode, plotGroup, calculator);

            setO(tpat);
        }
        osgGA::GUIEventHandlerQtQml::Index::componentComplete();
    }

    TerrainProfileAnalysisToolQtQml::TerrainProfileAnalysisToolQtQml(QObject* parent)
        : osgGA::GUIEventHandlerQtQml(parent)
    {
    }

    TerrainProfileAnalysisToolQtQml::TerrainProfileAnalysisToolQtQml(TerrainProfileAnalysisToolQtQml::Index* index, QObject* parent)
        : osgGA::GUIEventHandlerQtQml(index, parent)
    {
    }

    void TerrainProfileAnalysisToolQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);
        i(this)->setQ(this);
        osgGA::GUIEventHandlerQtQml::classBegin();
    }

    osgEarth::MapNodeQtQml* TerrainProfileAnalysisToolQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    osg::GroupQtQml* TerrainProfileAnalysisToolQtQml::hudGroup() const
    {
        return osg::GroupQtQml::fromGroup(i(this)->hudGroup);
    }

    osg::GroupQtQml* TerrainProfileAnalysisToolQtQml::plotGroup() const
    {
        return osg::GroupQtQml::fromGroup(i(this)->plotGroup);
    }

    QVariantList TerrainProfileAnalysisToolQtQml::profile()
    {
        return i(this)->profile;
    }

    double TerrainProfileAnalysisToolQtQml::minElevation() const
    {
        return i(this)->minElevation;
    }

    double TerrainProfileAnalysisToolQtQml::maxElevation() const
    {
        return i(this)->maxElevation;
    }

    double TerrainProfileAnalysisToolQtQml::totalDistance() const
    {
        return i(this)->totalDistance;
    }

    void TerrainProfileAnalysisToolQtQml::addProfilePoint(float distance, float elevation)
    {
        i(this)->profile.append(QVariant(QPointF(static_cast<float>(distance), static_cast<float>(elevation))));
    }

    void TerrainProfileAnalysisToolQtQml::clearProfilePoints()
    {
        i(this)->profile.clear();
    }

    void TerrainProfileAnalysisToolQtQml::setMinElevation(double value)
    {
        i(this)->minElevation = value;
    }

    void TerrainProfileAnalysisToolQtQml::setMaxElevation(double value)
    {
        i(this)->maxElevation = value;
    }

    void TerrainProfileAnalysisToolQtQml::setTotalDistance(double value)
    {
        i(this)->totalDistance = value;
    }

    void TerrainProfileAnalysisToolQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (mapNode) {
            if (!isComplete()) {
                i(this)->mapNode = mapNode->mapNode();
                return;
            }
            i(this)->mapNode = mapNode->mapNode();
            emit mapNodeChanged(mapNode);
        }
    }

    void TerrainProfileAnalysisToolQtQml::setHudGroup(osg::GroupQtQml* hudGroup)
    {
        if (!isComplete()) {
            i(this)->hudGroup = hudGroup->group();
            return;
        }

        i(this)->hudGroup = hudGroup->group();

        emit hudGroupChanged(hudGroup);
    }

    void TerrainProfileAnalysisToolQtQml::setPlotGroup(osg::GroupQtQml* plotGroup)
    {
        if (!isComplete()) {
            i(this)->plotGroup = plotGroup->group();
            return;
        }

        i(this)->plotGroup = plotGroup->group();

        emit plotGroupChanged(plotGroup);
    }
}
}
