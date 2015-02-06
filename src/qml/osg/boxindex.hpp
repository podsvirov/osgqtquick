#ifndef _OSG_BOX_QTQML_INDEX_
#define _OSG_BOX_QTQML_INDEX_ 1

#include <osg/BoxQtQml>

#include <osg/ShapeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT BoxQtQml::Index : public ShapeQtQml::Index
{
    friend class BoxQtQml;

public:
    Index(Box *o = 0);

    void classBegin();

protected:
    Box *othis;
    BoxQtQml *qthis;
};

}

#endif // _OSG_BOX_QTQML_INDEX_
