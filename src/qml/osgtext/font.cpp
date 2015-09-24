#include "font.hpp"
#include "fontindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Font>

#include <QDebug>

/*!
   \qmltype Style
   \inherits osg::Object
   \inqmlmodule osgText
   \brief Text style
 */

namespace osgText {

FontQtQml::Index::Index(Font *font) :
    ObjectQtQml::Index(font),
    qthis(0)
{
    othis = font;
}

void FontQtQml::Index::classBegin()
{
    if(!othis) othis = new Font();

    ObjectQtQml::Index::othis = othis;
    ObjectQtQml::Index::qthis = qthis;

    ObjectQtQml::Index::classBegin();
}

void FontQtQml::Index::componentComplete()
{
    ObjectQtQml::Index::othis = othis;
    ObjectQtQml::Index::qthis = qthis;

    ObjectQtQml::Index::componentComplete();
}

FontQtQml::FontQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

FontQtQml::FontQtQml(FontQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void FontQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ObjectQtQml::classBegin();
}

/*!
   \qmlproperty real osgText::Font::glyphImageMarginRatio

   The text glyph image margin ratio
 */

qreal FontQtQml::getGlyphImageMarginRatio() const
{
    return static_cast<qreal>(static_cast<Index*>(i)->othis->getGlyphImageMarginRatio());
}

void FontQtQml::setGlyphImageMarginRatio(qreal widthRation)
{
    if(getGlyphImageMarginRatio() == widthRation) return;

    static_cast<Index*>(i)->othis->setGlyphImageMarginRatio(static_cast<float>(widthRation));

    emit glyphImageMarginRatioChanged(widthRation);
}

Font *FontQtQml::font()
{
    return static_cast<Index*>(i)->othis;
}

FontQtQml *FontQtQml::fromFont(Font *font, QObject *parent)
{
    if(!font) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(font))
    {
        return static_cast<Index*>(index)->qthis;
    }

    FontQtQml *result = new FontQtQml(new Index(font), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
