#ifndef _OSGEARTHUTIL_MEASURETOOL_QTQML_INDEX_
#define _OSGEARTHUTIL_MEASURETOOL_QTQML_INDEX_ 1

#include "measuretoolhandler.hpp"
#include <osg/ObjectQtQml>
#include <osgGA/GUIEventHandlerQtQmlIndex>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT MeasureRecordQtQml::Index : public osgQtQml::Index {
    public:
        typedef MeasureRecord OType;
        typedef MeasureRecordQtQml QType;
        friend class MeasureRecordQtQml;

    public:
        Index(MeasureRecord* o = 0);
        void classBegin();
    };

    class OSGQTQML_EXPORT MeasureToolHandlerQtQml::Index : public osgGA::GUIEventHandlerQtQml::Index {
    public:
        typedef MeasureToolHandlerEx OType;
        typedef MeasureToolHandlerQtQml QType;
        friend class MeasureToolHandlerQtQml;

    public:
        Index(MeasureToolHandlerEx* o = 0);
        void classBegin();
        void componentComplete();

        bool path;
        bool circle;
        double distance;
        osg::Group* group;
        MapNode* mapNode;
    };
}
}

#endif
