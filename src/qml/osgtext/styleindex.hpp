#ifndef _OSGTEXT_STYLE_QTQML_INDEX_
#define _OSGTEXT_STYLE_QTQML_INDEX_ 1

#include <osgText/StyleQtQml>

#include <osg/ObjectQtQmlIndex>

namespace osgText {

class OSGQTQML_EXPORT StyleQtQml::Index : public osg::ObjectQtQml::Index
{
public:
    typedef Style OType;
    typedef StyleQtQml QType;
    friend class StyleQtQml;

public:
    Index(Style *o = 0);

    void classBegin();
};

}

#endif // _OSGTEXT_STYLE_QTQML_INDEX_
