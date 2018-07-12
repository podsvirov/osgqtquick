#include "font.hpp"
#include "fontindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Font>

#include <QtCore/QDebug>

/*!
   \qmltype Font
   \inherits osg::Object
   \inqmlmodule osgText
   \brief Text style
 */

namespace osgText {

FontQtQml::Index::Index(Font *font) :
    ObjectQtQml::Index(font),
    implementation(0)
{
}

void FontQtQml::Index::componentComplete()
{
    if(!o(this)) {
        setO(implementation
             ? new Font(implementation->fontImplementation())
             : new Font());
    }

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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ObjectQtQml::classBegin();
}

/*!
   \qmlproperty osgText::FontImplementation osgText::Font::implementation

   Concrete font implementation
 */

FontImplementationQtQml *FontQtQml::getImplementation()
{
    if (!isComplete())
    {
        return i(this)->implementation;
    }

    return FontImplementationQtQml::fromFontImplementation(
                o(this)->getImplementation());
}

void FontQtQml::setImplementation(FontImplementationQtQml *implementation)
{
    if (!isComplete())
    {
        i(this)->implementation = implementation;
        emit implementationChanged(implementation);
    }
    else
    {
        if(o(this)->getImplementation() ==
                implementation->fontImplementation()) return;

        o(this)->setImplementation(implementation->fontImplementation());

        emit implementationChanged(implementation);
    }
}

#if OSG_VERSION_LESS_THAN(3, 6, 0)
/*!
   \qmlproperty real osgText::Font::glyphImageMarginRatio

   The text glyph image margin ratio

   \note This property was removed since OSG 3.6.0.
 */

qreal FontQtQml::getGlyphImageMarginRatio() const
{
    return static_cast<qreal>(o(this)->getGlyphImageMarginRatio());
}

void FontQtQml::setGlyphImageMarginRatio(qreal widthRation)
{
    if(getGlyphImageMarginRatio() == widthRation) return;

    o(this)->setGlyphImageMarginRatio(static_cast<float>(widthRation));

    emit glyphImageMarginRatioChanged(widthRation);
}
#endif // OSG_VERSION_LESS_THAN(3, 6, 0)

Font *FontQtQml::font()
{
    return o(this);
}

FontQtQml *FontQtQml::fromFont(Font *font, QObject *parent)
{
    if(!font) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(font))
    {
        return static_cast<FontQtQml*>(index->qtObject());
    }

    FontQtQml *result = new FontQtQml(new Index(font), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
