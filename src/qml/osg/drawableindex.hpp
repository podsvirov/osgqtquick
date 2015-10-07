#ifndef _OSG_DRAWABLE_QTQML_INDEX_
#define _OSG_DRAWABLE_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/DrawableQtQml>

namespace osg {

class OSGQTQML_EXPORT DrawableQtQml::Index : public ObjectQtQml::Index
{
public:
    typedef Drawable OType;
    typedef DrawableQtQml QType;
    friend class DrawableQtQml;

public:
    Index(Drawable *o = 0);
};

}

#endif // _OSG_DRAWABLE_QTQML_INDEX_
