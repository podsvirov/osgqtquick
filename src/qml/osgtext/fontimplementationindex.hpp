#ifndef _OSGTEXT_FONTIMPLEMENTATION_QTQML_INDEX_
#define _OSGTEXT_FONTIMPLEMENTATION_QTQML_INDEX_ 1

#include <osgText/FontImplementationQtQml>

#include <osgQtQml/Index>

namespace osgText {

class OSGQTQML_EXPORT FontImplementationQtQml::Index : public osgQtQml::Index
{
public:
    typedef Font::FontImplementation OType;
    typedef FontImplementationQtQml QType;
    friend class FontImplementationQtQml;

public:
    Index(Font::FontImplementation *o = 0);
};

}

#endif // _OSGTEXT_FONTIMPLEMENTATION_QTQML_INDEX_
