#include "fontimplementation.hpp"
#include "fontimplementationindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Font>

#include <QDebug>

/*!
   \qmltype FontImplementation
   \inherits osg::Referenced
   \inqmlmodule osgText
   \brief Base type for font implementation
 */

namespace osgText {

FontImplementationQtQml::Index::Index(Font::FontImplementation *implementation) :
    osgQtQml::Index(implementation),
    qthis(0)
{
    othis = implementation;
}

void FontImplementationQtQml::Index::classBegin()
{
    if(othis) setO(othis);
    if(qthis) setQ(qthis);

    osgQtQml::Index::classBegin();
}

void FontImplementationQtQml::Index::componentComplete()
{
    if(othis) setO(othis);
    if(qthis) setQ(qthis);

    osgQtQml::Index::componentComplete();
}

FontImplementationQtQml::FontImplementationQtQml(QObject *parent) :
  osgQtQml::Object(parent)
{
}

FontImplementationQtQml::FontImplementationQtQml(FontImplementationQtQml::Index *index, QObject *parent) :
  osgQtQml::Object(index, parent)
{
}

void FontImplementationQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    Object::classBegin();
}

Font::FontImplementation *FontImplementationQtQml::fontImplementation()
{
    return static_cast<Index*>(_i_ptr)->othis;
}

FontImplementationQtQml *FontImplementationQtQml::fromFontImplementation(
        Font::FontImplementation *implementation, QObject *parent)
{
    if(!implementation) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(implementation))
    {
        return static_cast<Index*>(index)->qthis;
    }

    FontImplementationQtQml *result = new FontImplementationQtQml(new Index(implementation), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
