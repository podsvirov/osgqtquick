#ifndef _OSG_DRAWABLE_QTQML_INDEX_
#define _OSG_DRAWABLE_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/DrawableQtQml>

namespace osg {

class OSGQTQML_EXPORT DrawableQtQml::Index : public ObjectQtQml::Index
{
    friend class DrawableQtQml;

public:
    Index(Drawable *o = 0);
    void classBegin();

protected:
    Drawable *othis;
    DrawableQtQml *qthis;
};

}

#endif // _OSG_DRAWABLE_QTQML_INDEX_
