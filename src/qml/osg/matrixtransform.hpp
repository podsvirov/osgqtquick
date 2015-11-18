#ifndef _OSG_MATRIXTRANSFORM_QTQML_
#define _OSG_MATRIXTRANSFORM_QTQML_ 1

#include <osg/TransformQtQml>

#include <QMatrix4x4>

namespace osg {

class MatrixTransform;

class OSGQTQML_EXPORT MatrixTransformQtQml : public TransformQtQml
{
  Q_OBJECT

  Q_PROPERTY(QMatrix4x4 matrix READ getMatrix WRITE setMatrix NOTIFY matrixChanged)

public:
  class Index;

  MatrixTransformQtQml(QObject *parent = 0);
  MatrixTransformQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QMatrix4x4 getMatrix() const;
  Q_INVOKABLE void setMatrix(const QMatrix4x4 &mat);

  MatrixTransform* asMatrixTransform();

  static MatrixTransformQtQml* fromMatrixTransform(MatrixTransform *transform, QObject *parent = 0);

signals:
  void matrixChanged(const QMatrix4x4 &mat) const;
};

}

#endif // _OSG_MATRIXTRANSFORM_QTQML_
