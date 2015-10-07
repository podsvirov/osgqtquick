#include "transform.hpp"
#include "transformindex.hpp"

#include <osgQtQml/Index>

#include <osg/Transform>

#include <QDebug>

/*!
   \qmltype Transform
   \inherits Group
   \inqmlmodule osg
   \brief Transformation group
 */

namespace osg {

TransformQtQml::Index::Index(Transform *transform) :
    GroupQtQml::Index(transform)
{
}

void TransformQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Transform);

    GroupQtQml::Index::classBegin();
}

TransformQtQml::TransformQtQml(QObject *parent) :
  GroupQtQml(parent)
{
}

TransformQtQml::TransformQtQml(TransformQtQml::Index *index, QObject *parent) :
  GroupQtQml(index, parent)
{
}

void TransformQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    GroupQtQml::classBegin();
}

Transform *TransformQtQml::transform()
{
    return o(this);
}

TransformQtQml *TransformQtQml::fromTransform(Transform *transform, QObject *parent)
{
    if(!transform) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(transform))
    {
        return static_cast<TransformQtQml*>(index->qtObject());
    }

    return new TransformQtQml(new Index(transform), parent);
}

}
