#include "qfontimplementation.hpp"
#include "qfontimplementationindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Font>

#include <QDebug>

/*!
   \qmltype QFontImplementation
   \inherits osgText::FontImplementation
   \inqmlmodule osgQt
   \brief QFont based font implementation
 */

namespace osgQt {

QFontImplementationQtQml::Index::Index(QFontImplementation *implementation) :
    osgText::FontImplementationQtQml::Index(implementation),
    qthis(0)
{
    othis = implementation;
}

void QFontImplementationQtQml::Index::classBegin()
{
    osgText::FontImplementationQtQml::Index::othis = othis;
    osgText::FontImplementationQtQml::Index::qthis = qthis;

    osgText::FontImplementationQtQml::Index::classBegin();
}

void QFontImplementationQtQml::Index::componentComplete()
{
    if(!othis) {
        othis = new QFontImplementation(font);
    }

    osgText::FontImplementationQtQml::Index::othis = othis;
    osgText::FontImplementationQtQml::Index::qthis = qthis;

    osgText::FontImplementationQtQml::Index::componentComplete();
}

QFontImplementationQtQml::QFontImplementationQtQml(QObject *parent) :
  osgText::FontImplementationQtQml(parent)
{
}

QFontImplementationQtQml::QFontImplementationQtQml(QFontImplementationQtQml::Index *index, QObject *parent) :
  osgText::FontImplementationQtQml(index, parent)
{
}

void QFontImplementationQtQml::classBegin()
{
    if(!_i_ptr) _i_ptr = new Index();
    static_cast<Index*>(_i_ptr)->qthis = this;
    Object::classBegin();
}

QFont QFontImplementationQtQml::getFont() const
{
    return static_cast<Index*>(_i_ptr)->font;
}

void QFontImplementationQtQml::setFont(const QFont &font)
{
    if(static_cast<Index*>(_i_ptr)->font == font) return;

    static_cast<Index*>(_i_ptr)->font = font;

    emit fontChanged(font);
}

QFontImplementation *QFontImplementationQtQml::qFontImplementation()
{
    return static_cast<Index*>(_i_ptr)->othis;
}

QFontImplementationQtQml *QFontImplementationQtQml::fromQFontImplementation(
        QFontImplementation *implementation, QObject *parent)
{
    if(!implementation) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(implementation))
    {
        return static_cast<Index*>(index)->qthis;
    }

    QFontImplementationQtQml *result = new QFontImplementationQtQml(new Index(implementation), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
