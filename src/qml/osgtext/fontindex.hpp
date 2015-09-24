#ifndef _OSGTEXT_FONT_QTQML_INDEX_
#define _OSGTEXT_FONT_QTQML_INDEX_ 1

#include <osgText/FontQtQml>

#include <osg/ObjectQtQmlIndex>

#include <osgText/Font>

namespace osgText {

class OSGQTQML_EXPORT FontQtQml::Index : public osg::ObjectQtQml::Index
{
    friend class FontQtQml;

public:
    Index(Font *o = 0);

    void classBegin();
    void componentComplete();

protected:
    Font *othis;
    FontQtQml *qthis;

    //osg::ref_ptr<Style> style;
};

}

#endif // _OSGTEXT_FONT_QTQML_INDEX_
