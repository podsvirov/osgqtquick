#ifndef _OSGTEXT_FONTIMPLEMENTATION_QTQML_INDEX_
#define _OSGTEXT_FONTIMPLEMENTATION_QTQML_INDEX_ 1

#include <osgText/FontImplementationQtQml>

#include <osgQtQml/Index>

namespace osgText {

class OSGQTQML_EXPORT FontImplementationQtQml::Index : public osgQtQml::Index
{
    friend class FontImplementationQtQml;

public:
    Index(Font::FontImplementation *o = 0);

    void classBegin();
    void componentComplete();

protected:
    Font::FontImplementation *othis;
    FontImplementationQtQml *qthis;
};

}

#endif // _OSGTEXT_FONTIMPLEMENTATION_QTQML_INDEX_
