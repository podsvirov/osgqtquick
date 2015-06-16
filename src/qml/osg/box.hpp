#ifndef _OSG_BOX_QTQML_
#define _OSG_BOX_QTQML_ 1

#include <osg/ShapeQtQml>
#include <QVector3D>
#include <QQuaternion>

namespace osg {

class Box;

class OSGQTQML_EXPORT BoxQtQml : public ShapeQtQml
{
  Q_OBJECT

  Q_PROPERTY(QVector3D center READ getCenter WRITE setCenter NOTIFY centerChanged)
  Q_PROPERTY(QVector3D halfLengths READ getHalfLengths WRITE setHalfLengths NOTIFY halfLengthsChanged)
  Q_PROPERTY(QQuaternion rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)

public:
  class Index;

  BoxQtQml(QObject *parent = 0);
  BoxQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QVector3D getCenter() const;
  Q_INVOKABLE void setCenter(const QVector3D &center);

  Q_INVOKABLE QVector3D getHalfLengths() const;
  Q_INVOKABLE void setHalfLengths(const QVector3D &halfLengths);

  Q_INVOKABLE QQuaternion getRotation() const;
  Q_INVOKABLE void setRotation(const QQuaternion &quat);

  Box* box();

  static BoxQtQml* fromBox(Box *box, QObject *parent = 0);

signals:
  void centerChanged(const QVector3D &center) const;
  void halfLengthsChanged(const QVector3D &halfLengths) const;
  void rotationChanged(const QQuaternion &quat) const;
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_
