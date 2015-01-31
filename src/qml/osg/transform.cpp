#include "transform.hpp"
#include "transformindex.hpp"

#include <osgQtQml/Index>

#include <osg/Transform>

#include <QDebug>

namespace osg {

TransformQtQml::Index::Index(Transform *transform) :
    GroupQtQml::Index(transform),
    qthis(0)
{
    othis = transform;
}

void TransformQtQml::Index::classBegin()
{
    if(!othis) othis = new Transform();
    GroupQtQml::Index::othis = othis;
    GroupQtQml::Index::qthis = qthis;

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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    GroupQtQml::classBegin();
}

Transform *TransformQtQml::transform()
{
    return static_cast<Index*>(i)->othis;
}

TransformQtQml *TransformQtQml::fromTransform(Transform *transform, QObject *parent)
{
    if(!transform) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(transform))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new TransformQtQml(new Index(transform), parent);
}

}
