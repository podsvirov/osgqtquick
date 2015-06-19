#ifndef _OSG_CAMERA_QTQML_
#define _OSG_CAMERA_QTQML_ 1

#include <osg/TransformQtQml>

#include <QColor>

namespace osg {

class Camera;

class OSGQTQML_EXPORT CameraQtQml : public TransformQtQml
{
  Q_OBJECT

  Q_PROPERTY(QColor clearColor READ getClearColor WRITE setClearColor NOTIFY clearColorChanged)

public:
  class Index;

  CameraQtQml(QObject *parent = 0);
  CameraQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QColor getClearColor() const;
  Q_INVOKABLE void setClearColor(const QColor &color);

  Camera* camera();

  static CameraQtQml* fromCamera(Camera *camera, QObject *parent = 0);

signals:
  void clearColorChanged(const QColor &color) const;
};

}

#endif // _OSG_CAMERA_QTQML_
