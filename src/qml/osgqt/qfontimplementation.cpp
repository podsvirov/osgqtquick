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
    osgText::FontImplementationQtQml::Index(implementation)
{
}

void QFontImplementationQtQml::Index::componentComplete()
{
    if(!o(this)) setO(new QFontImplementation(font));

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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgText::FontImplementationQtQml::classBegin();
}

QFont QFontImplementationQtQml::getFont() const
{
    return i(this)->font;
}

void QFontImplementationQtQml::setFont(const QFont &font)
{
    if(i(this)->font == font) return;

    i(this)->font = font;

    emit fontChanged(font);
}

QFontImplementation *QFontImplementationQtQml::qFontImplementation()
{
    return o(this);
}

QFontImplementationQtQml *QFontImplementationQtQml::fromQFontImplementation(
        QFontImplementation *implementation, QObject *parent)
{
    if(!implementation) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(implementation))
    {
        return static_cast<QFontImplementationQtQml*>(index->qtObject());
    }

    QFontImplementationQtQml *result = new QFontImplementationQtQml(new Index(implementation), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
