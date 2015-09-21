#include "style.hpp"
#include "styleindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Style>

#include <QDebug>

/*!
   \qmltype Style
   \inherits osg::Object
   \inqmlmodule osgText
   \brief Text style
 */

namespace osgText {

StyleQtQml::Index::Index(Style *style) :
    ObjectQtQml::Index(style),
    qthis(0)
{
    othis = style;
}

void StyleQtQml::Index::classBegin()
{
    if(!othis) othis = new Style();

    ObjectQtQml::Index::othis = othis;
    ObjectQtQml::Index::qthis = qthis;

    ObjectQtQml::Index::classBegin();
}

void StyleQtQml::Index::componentComplete()
{
    ObjectQtQml::Index::othis = othis;
    ObjectQtQml::Index::qthis = qthis;

    ObjectQtQml::Index::componentComplete();
}

StyleQtQml::StyleQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

StyleQtQml::StyleQtQml(StyleQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void StyleQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ObjectQtQml::classBegin();
}

/*
StyleQtQml *StyleQtQml::getStyle() const
{
    return static_cast<Index*>(i)->getStyle();
}

void StyleQtQml::setStyle(StyleQtQml *style)
{
    static_cast<Index*>(i)->setStyle(style);
}
*/

/*!
   \qmlproperty real osgText::Style::widthRatio

   The text width ratio
 */

qreal StyleQtQml::getWidthRatio() const
{
    return static_cast<qreal>(static_cast<Index*>(i)->othis->getWidthRatio());
}

void StyleQtQml::setWidthRatio(qreal widthRation)
{
    if(getWidthRatio() == widthRation) return;

    static_cast<Index*>(i)->othis->setWidthRatio(static_cast<float>(widthRation));

    emit widthRatioChanged(widthRation);
}

Style *StyleQtQml::style()
{
    return static_cast<Index*>(i)->othis;
}

StyleQtQml *StyleQtQml::fromStyle(Style *style, QObject *parent)
{
    if(!style) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(style))
    {
        return static_cast<Index*>(index)->qthis;
    }

    StyleQtQml *result = new StyleQtQml(new Index(style), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
