#ifndef _OSGTEXT_STYLE_QTQML_INDEX_
#define _OSGTEXT_STYLE_QTQML_INDEX_ 1

#include <osgText/StyleQtQml>

#include <osg/ObjectQtQmlIndex>

#include <osg/Shape>

namespace osgText {

class OSGQTQML_EXPORT StyleQtQml::Index : public osg::ObjectQtQml::Index
{
    friend class StyleQtQml;

public:
    Index(Style *o = 0);

    void classBegin();
    void componentComplete();

protected:
    Style *othis;
    StyleQtQml *qthis;

    //osg::ref_ptr<Style> style;
};

}

#endif // _OSGTEXT_STYLE_QTQML_INDEX_
