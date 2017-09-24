#ifndef _OSGEARTHUTIL_VIEW_COORDS_TOOL_QTQML_INDEX_
#define _OSGEARTHUTIL_VIEW_COORDS_TOOL_QTQML_INDEX_

#include "viewcoordstool.hpp"
#include <osgGA/GUIEventHandlerQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT ViewCoordsToolQtQml::Index : public osgGA::GUIEventHandlerQtQml::Index {
    public:
        typedef ViewCoordsTool OType;
        typedef ViewCoordsToolQtQml QType;
        friend class ViewCoordsToolQtQml;

    public:
        Index(ViewCoordsTool* o = 0);
        void classBegin();

        QGeoCoordinate viewCoord;
        QGeoCoordinate mouseCoord;
        double heading;
        EarthManipulator* manip;
        MapNode* mapNode;
        QGeoCoordinate eye;
    };
}
}

#endif
