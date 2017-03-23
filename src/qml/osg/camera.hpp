#ifndef _OSG_CAMERA_QTQML_
#define _OSG_CAMERA_QTQML_ 1

#include <osg/TransformQtQml>

#include <QtGui/QColor>

namespace osg {

class Camera;

class OSGQTQML_EXPORT CameraQtQml : public TransformQtQml
{
  Q_OBJECT

  Q_PROPERTY(QColor clearColor READ getClearColor WRITE setClearColor NOTIFY clearColorChanged)
  Q_PROPERTY(double nearFarRatio READ getNearFarRatio WRITE setNearFarRatio NOTIFY nearFarRatioChanged)

public:
  class Index;

  CameraQtQml(QObject *parent = 0);
  CameraQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QColor getClearColor() const;
  Q_INVOKABLE void setClearColor(const QColor &color);

  Q_INVOKABLE double getNearFarRatio() const;
  Q_INVOKABLE void setNearFarRatio(const double ratio);

  Camera* camera();

  static CameraQtQml* fromCamera(Camera *camera, QObject *parent = 0);

Q_SIGNALS:
  void clearColorChanged(const QColor &color) const;
  void nearFarRatioChanged(const double ratio) const;
};

}

#endif // _OSG_CAMERA_QTQML_
