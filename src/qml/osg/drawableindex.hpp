#ifndef _OSG_DRAWABLE_QTQML_INDEX_
#define _OSG_DRAWABLE_QTQML_INDEX_ 1

#include <osg/NodeQtQmlIndex>

#include <osg/DrawableQtQml>

namespace osg {

class OSGQTQML_EXPORT DrawableQtQml::Index : public NodeQtQml::Index
{
public:
    typedef Drawable OType;
    typedef DrawableQtQml QType;
    friend class DrawableQtQml;

public:
    Index(Drawable *o = 0);

    void classBegin();
};

}

#endif // _OSG_DRAWABLE_QTQML_INDEX_
