#ifndef _OSGTEXT_TEXTBASE_QTQML_INDEX_
#define _OSGTEXT_TEXTBASE_QTQML_INDEX_ 1

#include <osgText/TextBaseQtQml>

#include <osg/DrawableQtQmlIndex>

#include <osg/Shape>

namespace osgText {

class FontQtQml;

class OSGQTQML_EXPORT TextBaseQtQml::Index : public osg::DrawableQtQml::Index
{
public:
    typedef TextBase OType;
    typedef TextBaseQtQml QType;
    friend class TextBaseQtQml;

public:
    Index(TextBase *o = 0);

    void componentComplete();

    void loadFontFromSource();

    void setColor(const QColor &color);

protected:
    QColor color;
    qreal characterSize;
    FontQtQml *font;
    QUrl fontSource;
};

}

#endif // _OSGTEXT_TEXTBASE_QTQML_INDEX_
