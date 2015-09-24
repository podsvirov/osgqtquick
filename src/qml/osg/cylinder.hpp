#ifndef _OSG_CYLINDER_QTQML_
#define _OSG_CYLINDER_QTQML_ 1

#include <osg/ShapeQtQml>
#include <QVector3D>

namespace osg {

class Cylinder;

class OSGQTQML_EXPORT CylinderQtQml : public ShapeQtQml
{
  Q_OBJECT

  Q_PROPERTY(QVector3D center READ getCenter WRITE setCenter NOTIFY centerChanged)
  Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged)
  Q_PROPERTY(float height READ getHeight WRITE setHeight NOTIFY heightChanged)

public:
  class Index;

  CylinderQtQml(QObject *parent = 0);
  CylinderQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QVector3D getCenter() const;
  Q_INVOKABLE void setCenter(const QVector3D &center);

  Q_INVOKABLE float getRadius() const;
  Q_INVOKABLE void setRadius(float radius);

  Q_INVOKABLE float getHeight() const;
  Q_INVOKABLE void setHeight(float height);

  Cylinder* cylinder();

  static CylinderQtQml* fromCylinder(Cylinder *cylinder, QObject *parent = 0);

signals:
  void centerChanged(const QVector3D &center) const;
  void radiusChanged(float radius);
  void heightChanged(float height);
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_
