#ifndef _OSGTEXT_TEXTBASE_QTQML_INDEX_
#define _OSGTEXT_TEXTBASE_QTQML_INDEX_ 1

#include <osgText/TextBaseQtQml>

#include <osg/DrawableQtQmlIndex>

#include <osg/Shape>

namespace osgText {

class OSGQTQML_EXPORT TextBaseQtQml::Index : public osg::DrawableQtQml::Index
{
    friend class TextBaseQtQml;

public:
    Index(TextBase *o = 0);

    void classBegin();
    void componentComplete();

    //StyleQtQml *getStyle() const;
    //void setStyle(StyleQtQml *style);

    void setColor(const QColor &color);

protected:
    TextBase *othis;
    TextBaseQtQml *qthis;

    //osg::ref_ptr<Style> style;
    QColor color;
    qreal characterSize;
};

}

#endif // _OSGTEXT_TEXTBASE_QTQML_INDEX_
