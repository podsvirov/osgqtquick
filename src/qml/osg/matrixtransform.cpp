#include "matrixtransform.hpp"
#include "matrixtransformindex.hpp"

#include <osg/MatrixTransform>

#include <QDebug>

/*!
   \qmltype MatrixTransform
   \inherits Transform
   \inqmlmodule osg
   \brief Transform via matrix 4x4
 */

namespace osg {

MatrixTransformQtQml::Index::Index(MatrixTransform *transform) :
    TransformQtQml::Index(transform)
{
}

void MatrixTransformQtQml::Index::classBegin()
{
    if(!o(this)) setO(new MatrixTransform);

    TransformQtQml::Index::classBegin();
}

MatrixTransformQtQml::MatrixTransformQtQml(QObject *parent) :
  TransformQtQml(parent)
{
}

MatrixTransformQtQml::MatrixTransformQtQml(MatrixTransformQtQml::Index *index, QObject *parent) :
  TransformQtQml(index, parent)
{
}

void MatrixTransformQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    TransformQtQml::classBegin();
}

/*!
   \qmlproperty matrix4x4 osg::MatrixTransform::matrix

   Matrix
 */

QMatrix4x4 MatrixTransformQtQml::getMatrix() const
{
    return osgQt::matrix(o(this)->getMatrix());
}

void MatrixTransformQtQml::setMatrix(const QMatrix4x4 &mat)
{
    if(mat == getMatrix()) return;

    o(this)->setMatrix(osgQt::matrix(mat));

    emit matrixChanged(mat);
}

MatrixTransform *MatrixTransformQtQml::asMatrixTransform()
{
    return o(this);
}

MatrixTransformQtQml *MatrixTransformQtQml::fromMatrixTransform(MatrixTransform *transform, QObject *parent)
{
    if(!transform) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(transform))
    {
        return static_cast<MatrixTransformQtQml*>(index->qtObject());
    }

    MatrixTransformQtQml *result = new MatrixTransformQtQml(new Index(transform), parent);
    result->classBegin();
    result->componentComplete();
    return result;
}

}
