#ifndef OSGEARTHUTIL_MOUSE_COORDS_TOOL_QTQML_INDEX_
#define OSGEARTHUTIL_MOUSE_COORDS_TOOL_QTQML_INDEX_ 1

#include "mousecoordstool.hpp"
#include <osgEarth/MapNode>
#include <osgGA/GUIEventHandlerQtQml>
#include <osgGA/GUIEventHandlerQtQmlIndex>

namespace osgEarth {
namespace Util {

    class OSGQTQML_EXPORT MouseCoordsToolQtQml::Index : public osgGA::GUIEventHandlerQtQml::Index {
    public:
        typedef MouseCoordsTool OType;
        typedef MouseCoordsToolQtQml QType;
        friend class MouseCoordsToolQtQml;

    public:
        Index(MouseCoordsTool* o = 0);
        void classBegin();
        void componentComplete();

        MouseCoordsCallback* callback;
        osgEarth::MapNode* mapNode;
        QGeoCoordinate position;
    };
}
}

#endif
