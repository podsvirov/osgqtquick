#ifndef _OSG_GEODE_QTQML_INDEX_
#define _OSG_GEODE_QTQML_INDEX_ 1

#include <osg/GeodeQtQml>

#include <osg/NodeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT GeodeQtQml::Index : public NodeQtQml::Index
{
    friend class GeodeQtQml;

public:
    Index(Geode *o = 0);

    void classBegin();

    bool addDrawable(DrawableQtQml *drawable);
    bool removeDrawable(DrawableQtQml *drawable);

protected:
    Geode *othis;
    GeodeQtQml *qthis;
};

}

#endif // _OSG_GEODE_QTQML_INDEX_
