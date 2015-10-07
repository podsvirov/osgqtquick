#include "textbase.hpp"
#include "textbaseindex.hpp"

#include <osgQtQml/Index>

#include <osgText/TextBase>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

#include <QFileInfo>
#include <QQmlContext>
#include <QQmlEngine>

#include <QDebug>

/*!
   \qmltype TextBase
   \inherits osg::Drawable
   \inqmlmodule osgText
   \brief Base type for text \l {osg::Node}{Nodes}
 */

namespace osgText {

TextBaseQtQml::Index::Index(TextBase *drawable) :
    DrawableQtQml::Index(drawable),
    characterSize(0),
    font(0)
{
}

void TextBaseQtQml::Index::componentComplete()
{
    DrawableQtQml::Index::componentComplete();

    osg::ref_ptr<Font> df = Font::getDefaultFont();

    if(font) {
        q(this)->setFont(font);
    } else if(!fontSource.isEmpty())
    {
        loadFontFromSource();
    }
    if(!o(this)->getFont()) {
        if(df.valid()) {
            o(this)->setFont(df);
        }
    }
}

void TextBaseQtQml::Index::loadFontFromSource()
{
    std::string file;

    if(fontSource.isLocalFile()) {
        QFileInfo info(fontSource.toLocalFile());
        if(info.exists())
        {
            file = info.filePath().toStdString();
        }
        else
        {
            if(QQmlContext *ctx = QQmlEngine::contextForObject(q(this)))
            {
                file = fontSource.toString().replace(
                            QFileInfo(ctx->baseUrl().toString()).path(),
                            "").toStdString();
            }
            file = osgText::findFontFile(file);
        }
    }
    else { // no local file
        file = fontSource.toString().remove("file:///").toStdString();
    }

    if(!file.empty())
    {
        o(this)->setFont(file);
        fontSource = QUrl::fromLocalFile(QString::fromStdString(file));
    }
}

void TextBaseQtQml::Index::setColor(const QColor &color)
{
    osg::Vec4 c = osgQt::swapColor(color);

    if(o(this)->getColor() == c) return;

    o(this)->setColor(c);

    emit q(this)->colorChanged(color);
}

TextBaseQtQml::TextBaseQtQml(QObject *parent) :
  DrawableQtQml(parent)
{
}

TextBaseQtQml::TextBaseQtQml(TextBaseQtQml::Index *index, QObject *parent) :
  DrawableQtQml(index, parent)
{
}

void TextBaseQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    DrawableQtQml::classBegin();
}

/*!
   \qmlproperty osgText::Style osgText::TextBase::style

   Text \l {osgText::Style}{style}
 */

StyleQtQml *TextBaseQtQml::getStyle()
{
    return StyleQtQml::fromStyle(o(this)->getStyle());
}

void TextBaseQtQml::setStyle(StyleQtQml *style)
{
    if(o(this)->getStyle() == style->style()) return;

    o(this)->setStyle(style->style());

    emit styleChanged(style);
}

/*!
   \qmlproperty osgText::Font osgText::TextBase::font

   Text \l {osgText::Font}{Font}
 */

FontQtQml *TextBaseQtQml::getFont() const
{
    // NOTE: const_cast...
    return FontQtQml::fromFont(const_cast<osgText::Font*>(o(this)->getFont()));
}

void TextBaseQtQml::setFont(FontQtQml *font)
{
    if(!isComplete())
    {
        static_cast<Index*>(_i_ptr)->font = font;
        return;
    }

    if(o(this)->getFont() == font->font()) return;

    o(this)->setFont(font->font());

    emit fontChanged(font);
}

/*!
   \qmlproperty url osgText::TextBase::fontSource

   This property holds the URL of the font file.
 */

QUrl TextBaseQtQml::getFontSource()
{
    return static_cast<Index*>(_i_ptr)->fontSource;
}

void TextBaseQtQml::setFontSource(const QUrl &source)
{
    //if(static_cast<Index*>(i)->fontSource == source) return;

    static_cast<Index*>(_i_ptr)->fontSource = source;

    if(isComplete()) {
        static_cast<Index*>(_i_ptr)->loadFontFromSource();
    }

    return fontSourceChanged(source);
}

/*!
   \qmlproperty color osgText::TextBase::color

   Color of \l {osgText::TextBase}{text}
 */

QColor TextBaseQtQml::getColor() const
{
    return osgQt::swapColor(o(this)->getColor());
}

void TextBaseQtQml::setColor(const QColor &color)
{
    static_cast<Index*>(_i_ptr)->setColor(color);
}

/*!
   \qmlproperty string osgText::TextBase::text

   The the text string
 */

QString TextBaseQtQml::getText() const
{
    return osgQt::swapString(o(this)->getText());
}

void TextBaseQtQml::setText(const QString &text)
{
    QString qText = getText();

    if(text == qText) return;

    o(this)->setText(osgQt::swapString(text));

    emit textChanged(text);
}

/*!
   \qmlproperty real osgText::TextBase::characterSize

   The the rendered character size in object coordinates
 */

qreal TextBaseQtQml::getCharacterSize() const
{
    return static_cast<qreal>(static_cast<Index*>(_i_ptr)->characterSize);
}

void TextBaseQtQml::setCharacterSize(qreal size)
{
    if(static_cast<Index*>(_i_ptr)->characterSize == size) return;

    // NOTE: osgText::TextBase has not getCharacterSize method?...
    // We cache it in index object now
    static_cast<Index*>(_i_ptr)->characterSize = size;
    o(this)->setCharacterSize(static_cast<float>(size));

    emit characterSizeChanged(size);
}

TextBaseQtQml::AxisAlignment TextBaseQtQml::getAxisAlignment() const
{
    return static_cast<AxisAlignment>(o(this)->getAxisAlignment());
}

void TextBaseQtQml::setAxisAlignment(TextBaseQtQml::AxisAlignment axisAlignment)
{
    if(getAxisAlignment() == axisAlignment) return;

    o(this)->setAxisAlignment(static_cast<TextBase::AxisAlignment>(axisAlignment));

    emit axisAlignmentChanged(axisAlignment);
}

TextBaseQtQml::DrawModeMasks TextBaseQtQml::getDrawMode() const
{
    return DrawModeMasks(o(this)->getDrawMode());
}

void TextBaseQtQml::setDrawMode(TextBaseQtQml::DrawModeMasks drawMode)
{
    if(getDrawMode() == drawMode) return;

    o(this)->setDrawMode(static_cast<TextBase::DrawModeMask>(static_cast<int>(drawMode)));

    emit drawModeChanged(drawMode);
}

TextBase *TextBaseQtQml::textBase()
{
    return o(this);
}

TextBaseQtQml *TextBaseQtQml::fromTextBase(TextBase *textBase, QObject *parent)
{
    if(!textBase) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(textBase))
    {
        return static_cast<TextBaseQtQml*>(index->qtObject());
    }

    TextBaseQtQml *result = new TextBaseQtQml(new Index(textBase), parent);
    result->classBegin();
    return result;
}

}
