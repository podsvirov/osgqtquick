#ifndef _OSGEARTHUTIL_ACTIVITY_MONITOR_TOOL_QTQML_INDEX_
#define _OSGEARTHUTIL_ACTIVITY_MONITOR_TOOL_QTQML_INDEX_ 1

#include "activitymonitortool.hpp"
#include <osgGA/GUIEventHandlerQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT ActivityMonitorToolQtQml::Index : public osgGA::GUIEventHandlerQtQml::Index {
    public:
        typedef ActivityMonitorTool OType;
        typedef ActivityMonitorToolQtQml QType;
        friend class ActivityMonitorToolQtQml;

    public:
        Index(ActivityMonitorTool* o = 0);
        void classBegin();
        void componentComplete();
    };
}
}

#endif
