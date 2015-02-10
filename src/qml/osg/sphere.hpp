#ifndef _OSG_SPHERE_QTQML_
#define _OSG_SPHERE_QTQML_ 1

#include <osg/ShapeQtQml>
#include <QVector3D>

namespace osg {

class Sphere;

class OSGQTQML_EXPORT SphereQtQml : public ShapeQtQml
{
  Q_OBJECT

  Q_PROPERTY(QVector3D center READ getCenter WRITE setCenter NOTIFY centerChanged)
  Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged)

public:
  class Index;

  SphereQtQml(QObject *parent = 0);
  SphereQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QVector3D getCenter() const;
  Q_INVOKABLE void setCenter(const QVector3D &center);

  Q_INVOKABLE float getRadius() const;
  Q_INVOKABLE void setRadius(float radius);

  Sphere* sphere();

  static SphereQtQml* fromSphere(Sphere *sphere, QObject *parent = 0);

signals:
  void centerChanged(const QVector3D &center) const;
  void radiusChanged(float arg);
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_
