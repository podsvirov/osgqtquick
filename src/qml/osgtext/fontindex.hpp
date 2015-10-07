#ifndef _OSGTEXT_FONT_QTQML_INDEX_
#define _OSGTEXT_FONT_QTQML_INDEX_ 1

#include <osgText/FontQtQml>

#include <osg/ObjectQtQmlIndex>

#include <osgText/Font>

namespace osgText {

class FontImplementationQtQml;

class OSGQTQML_EXPORT FontQtQml::Index : public osg::ObjectQtQml::Index
{
public:
    typedef Font OType;
    typedef FontQtQml QType;
    friend class FontQtQml;

public:
    Index(Font *o = 0);

    void classBegin();
    void componentComplete();

protected:
    FontImplementationQtQml *implementation;
};

}

#endif // _OSGTEXT_FONT_QTQML_INDEX_
