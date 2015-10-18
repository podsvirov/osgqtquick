#include "text3d.hpp"
#include "text3dindex.hpp"

#include <osgText/Text3D>

#include <osgQt/QFontImplementation>

#include <QDebug>

/*!
   \qmltype Text3D
   \inherits TextBase
   \inqmlmodule osgText
   \brief 3-dimensional text
 */

namespace osgText {

Text3DQtQml::Index::Index(Text3D *text3D) :
    TextBaseQtQml::Index(text3D)
{
}

void Text3DQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Text3D);

    TextBaseQtQml::Index::classBegin();
}

Text3DQtQml::Text3DQtQml(QObject *parent) :
  TextBaseQtQml(parent)
{
}

Text3DQtQml::Text3DQtQml(Text3DQtQml::Index *index, QObject *parent) :
  TextBaseQtQml(index, parent)
{
}

void Text3DQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    TextBaseQtQml::classBegin();
}

/*!
   \qmlproperty real osgText::Text3D::characterDepth

   The Charactere Depth of text
 */

qreal Text3DQtQml::getCharacterDepth() const
{
    return static_cast<qreal>(o(this)->getCharacterDepth());
}

void Text3DQtQml::setCharacterDepth(qreal depth)
{
    if(getCharacterDepth() == depth) return;

    o(this)->setCharacterDepth(static_cast<float>(depth));

    emit characterDepthChanged(depth);
}

Text3D *Text3DQtQml::text3D()
{
    return o(this);
}

Text3DQtQml *Text3DQtQml::fromText3D(Text3D *text3D, QObject *parent)
{
    if(!text3D) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(text3D))
    {
        return static_cast<Text3DQtQml*>(index->qtObject());
    }

    Text3DQtQml *result = new Text3DQtQml(new Index(text3D), parent);
    result->classBegin();
    return result;
}

}
