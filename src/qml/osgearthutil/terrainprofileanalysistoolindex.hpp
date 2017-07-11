#ifndef _OSGEARTHUTIL_TERRAINPROFILEANALYSISTOOL_QTQML_INDEX_
#define _OSGEARTHUTIL_TERRAINPROFILEANALYSISTOOL_QTQML_INDEX_ 1

#include "terrainprofileanalysistool.hpp"
#include <osgGA/GUIEventHandlerQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT TerrainProfileAnalysisToolQtQml::Index : public osgGA::GUIEventHandlerQtQml::Index {
    public:
        typedef TerrainProfileAnalysisTool OType;
        typedef TerrainProfileAnalysisToolQtQml QType;
        friend class TerrainProfileAnalysisToolQtQml;

    public:
        Index(TerrainProfileAnalysisTool* o = 0);
        void classBegin();
        void componentComplete();

        osgEarth::MapNode* mapNode;
        osg::Group* hudGroup;
        osg::Group* plotGroup;

        QVariantList profile;
        double minElevation;
        double maxElevation;
        double totalDistance;
    };
}
}

#endif
