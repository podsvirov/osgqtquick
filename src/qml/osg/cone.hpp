#ifndef _OSG_CONE_QTQML_
#define _OSG_CONE_QTQML_ 1

#include <osg/ShapeQtQml>
#include <QtGui/QVector3D>

namespace osg {

class Cone;

class OSGQTQML_EXPORT ConeQtQml : public ShapeQtQml
{
  Q_OBJECT

  Q_PROPERTY(QVector3D center READ getCenter WRITE setCenter NOTIFY centerChanged)
  Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged)
  Q_PROPERTY(float height READ getHeight WRITE setHeight NOTIFY heightChanged)

public:
  class Index;

  ConeQtQml(QObject *parent = 0);
  ConeQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QVector3D getCenter() const;
  Q_INVOKABLE void setCenter(const QVector3D &center);

  Q_INVOKABLE float getRadius() const;
  Q_INVOKABLE void setRadius(float radius);

  Q_INVOKABLE float getHeight() const;
  Q_INVOKABLE void setHeight(float height);

  Cone* cone();

  static ConeQtQml* fromCone(Cone *cone, QObject *parent = 0);

Q_SIGNALS:
  void centerChanged(const QVector3D &center) const;
  void radiusChanged(float radius);
  void heightChanged(float height);
};

}

#endif // _OSG_CONE_QTQML_
