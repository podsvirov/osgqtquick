#ifndef _OSGTEXT_TEXT3D_QTQML_INDEX_
#define _OSGTEXT_TEXT3D_QTQML_INDEX_ 1

#include <osgText/Text3DQtQml>

#include <osgText/TextBaseQtQmlIndex>

namespace osgText {

class OSGQTQML_EXPORT Text3DQtQml::Index : public TextBaseQtQml::Index
{
    friend class Text3DQtQml;

public:
    Index(Text3D *Text3D = 0);

    void classBegin();
    void componentComplete();

protected:
    Text3D *othis;
    Text3DQtQml *qthis;
};

}

#endif // _OSGTEXT_TEXT3D_QTQML_INDEX_
