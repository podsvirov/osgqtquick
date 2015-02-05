#ifndef _OSG_SHAPEDRAWABLE_QTQML_INDEX_
#define _OSG_SHAPEDRAWABLE_QTQML_INDEX_ 1

#include <osg/ShapeDrawableQtQml>

#include <osg/DrawableQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT ShapeDrawableQtQml::Index : public DrawableQtQml::Index
{
    friend class ShapeDrawableQtQml;

public:
    Index(ShapeDrawable *o = 0);

    void classBegin();

protected:
    ShapeDrawable *othis;
    ShapeDrawableQtQml *qthis;
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_INDEX_
