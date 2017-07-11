#ifndef _OSGEARTHUTIL_TERRAINPROFILEANALYSISTOOL_QTQML_
#define _OSGEARTHUTIL_TERRAINPROFILEANALYSISTOOL_QTQML_ 1

#include <QPointF>
#include <QQmlListProperty>
#include <osg/GroupQtQml>
#include <osgEarth/MapNode>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthFeatures/Feature>
#include <osgEarthUtil/TerrainProfile>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventHandlerQtQml>
#include <osgText/Font>
#include <osgText/Text>

namespace osgEarth {
namespace Util {
    class TerrainProfileAnalysisToolQtQml;
    class TerrainProfileAnalysisTool : public osgGA::GUIEventHandler {
    public:
        TerrainProfileAnalysisTool(TerrainProfileAnalysisToolQtQml* tpatQtQml, osgEarth::MapNode* mapNode, osg::Group* root, TerrainProfileCalculator* profileCalculator);
        bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
        void compute();

    public:
        TerrainProfileAnalysisToolQtQml* toolQml;
        osgEarth::MapNode* mapNode;
        osg::Group* root;
        TerrainProfileCalculator* profileCalculator;
        osg::ref_ptr<osgEarth::Annotation::FeatureNode> featureNode;
        bool startValid;
        osg::Vec3d start;
        osg::Vec3d end;
    };

    class OSGQTQML_EXPORT TerrainProfileAnalysisToolQtQml : public osgGA::GUIEventHandlerQtQml {
        Q_OBJECT
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(osg::GroupQtQml* hudGroup READ hudGroup WRITE setHudGroup NOTIFY hudGroupChanged)
        Q_PROPERTY(osg::GroupQtQml* plotGroup READ plotGroup WRITE setPlotGroup NOTIFY plotGroupChanged)
        Q_PROPERTY(QVariantList profile READ profile NOTIFY profileChanged)
        Q_PROPERTY(double minElevation READ minElevation)
        Q_PROPERTY(double maxElevation READ maxElevation)
        Q_PROPERTY(double totalDistance READ totalDistance)

    public:
        class Index;
        TerrainProfileAnalysisToolQtQml(QObject* parent = 0);
        TerrainProfileAnalysisToolQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();
        osgEarth::MapNodeQtQml* mapNode() const;
        osg::GroupQtQml* hudGroup() const;
        osg::GroupQtQml* plotGroup() const;

        QVariantList profile();

        double minElevation() const;
        double maxElevation() const;
        double totalDistance() const;

        void addProfilePoint(float distance, float elevation);
        void clearProfilePoints();
        void setMinElevation(double value);
        void setMaxElevation(double value);
        void setTotalDistance(double value);

    public slots:
        void
        setMapNode(osgEarth::MapNodeQtQml* mapNode);
        void setHudGroup(osg::GroupQtQml* hudGroup);
        void setPlotGroup(osg::GroupQtQml* plotGroup);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
        void hudGroupChanged(osg::GroupQtQml* hudGroup);
        void plotGroupChanged(osg::GroupQtQml* plotGroup);
        void profileChanged();
    };
}
}

#endif
