#include "style.hpp"
#include "styleindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Style>

#include <QtCore/QDebug>

/*!
   \qmltype Style
   \inherits osg::Object
   \inqmlmodule osgText
   \brief Text font
 */

namespace osgText {

StyleQtQml::Index::Index(Style *style) :
    ObjectQtQml::Index(style)
{
}

void StyleQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Style);

    ObjectQtQml::Index::classBegin();
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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

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
    return static_cast<qreal>(o(this)->getWidthRatio());
}

void StyleQtQml::setWidthRatio(qreal widthRation)
{
    if(getWidthRatio() == widthRation) return;

    o(this)->setWidthRatio(static_cast<float>(widthRation));

    emit widthRatioChanged(widthRation);
}

Style *StyleQtQml::style()
{
    return o(this);
}

StyleQtQml *StyleQtQml::fromStyle(Style *style, QObject *parent)
{
    if(!style) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(style))
    {
        return static_cast<StyleQtQml*>(index->qtObject());
    }

    StyleQtQml *result = new StyleQtQml(new Index(style), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
