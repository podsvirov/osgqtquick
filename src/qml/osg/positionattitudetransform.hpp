#ifndef _OSG_POSITIONATTITUDETRANSFORM_QTQML_
#define _OSG_POSITIONATTITUDETRANSFORM_QTQML_ 1

#include <osg/TransformQtQml>

#include <QtGui/QVector3D>
#include <QtGui/QQuaternion>

namespace osg {

class PositionAttitudeTransform;

class OSGQTQML_EXPORT PositionAttitudeTransformQtQml : public TransformQtQml
{
  Q_OBJECT

  Q_PROPERTY(QVector3D position READ getPosition WRITE setPosition NOTIFY positionChanged)
  Q_PROPERTY(QQuaternion attitude READ getAttitude WRITE setAttitude NOTIFY attitudeChanged)
  Q_PROPERTY(QVector3D scale READ getScale WRITE setScale NOTIFY scaleChanged)
  Q_PROPERTY(QVector3D pivotPoint READ getPivotPoint WRITE setPivotPoint NOTIFY pivotPointChanged)

public:
  class Index;

  PositionAttitudeTransformQtQml(QObject *parent = 0);
  PositionAttitudeTransformQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QVector3D getPosition() const;
  Q_INVOKABLE void setPosition(const QVector3D &pos);

  Q_INVOKABLE QQuaternion getAttitude() const;
  Q_INVOKABLE void setAttitude(const QQuaternion &quat);

  Q_INVOKABLE QVector3D getScale() const;
  Q_INVOKABLE void setScale(const QVector3D &scale);

  Q_INVOKABLE QVector3D getPivotPoint() const;
  Q_INVOKABLE void setPivotPoint(const QVector3D &pivot);

  PositionAttitudeTransform* asPositionAttitudeTransform();

  static PositionAttitudeTransformQtQml* fromPositionAttitudeTransform(PositionAttitudeTransform *transform, QObject *parent = 0);

Q_SIGNALS:
  void positionChanged(const QVector3D &pos) const;
  void attitudeChanged(const QQuaternion &quat) const;
  void scaleChanged(const QVector3D &scale) const;
  void pivotPointChanged(const QVector3D &pivot) const;
};

}

#endif // _OSG_POSITIONATTITUDETRANSFORM_QTQML_
