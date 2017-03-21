#include "fontimplementation.hpp"
#include "fontimplementationindex.hpp"

#include <osgQtQml/Index>

#include <osgText/Font>

#include <QtCore/QDebug>

/*!
   \qmltype FontImplementation
   \inherits osg::Referenced
   \inqmlmodule osgText
   \brief Base type for font implementation
 */

namespace osgText {

FontImplementationQtQml::Index::Index(Font::FontImplementation *implementation) :
    osgQtQml::Index(implementation)
{
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

    osgQtQml::Object::classBegin();
}

Font::FontImplementation *FontImplementationQtQml::fontImplementation()
{
    return o(this);
}

FontImplementationQtQml *FontImplementationQtQml::fromFontImplementation(
        Font::FontImplementation *implementation, QObject *parent)
{
    if(!implementation) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(implementation))
    {
        return static_cast<FontImplementationQtQml*>(index->qtObject());
    }

    FontImplementationQtQml *result = new FontImplementationQtQml(new Index(implementation), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
