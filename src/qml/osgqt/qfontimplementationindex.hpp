#ifndef _OSGQT_QFONTIMPLEMENTATION_QTQML_INDEX_
#define _OSGQT_QFONTIMPLEMENTATION_QTQML_INDEX_ 1

#include <osgQt/QFontImplementationQtQml>

#include <osgText/FontImplementationQtQmlIndex>

#include <osgQt/QFontImplementation>

namespace osgQt {

class OSGQTQML_EXPORT QFontImplementationQtQml::Index :
    public osgText::FontImplementationQtQml::Index
{
public:
    typedef osgQt::QFontImplementation OType;
    typedef QFontImplementationQtQml QType;
    friend class QFontImplementationQtQml;

public:
    Index(QFontImplementation *o = 0);

    void componentComplete();

protected:
    QFont font;
};

}

#endif // _OSGQT_QFONTIMPLEMENTATION_QTQML_INDEX_
