#ifndef _OSG_CAMERA_QTQML_
#define _OSG_CAMERA_QTQML_ 1

#include <osg/GroupQtQml>

namespace osg {

class Camera;

class OSGQTQML_EXPORT CameraQtQml : public GroupQtQml
{
  Q_OBJECT

public:
  class Index;

  CameraQtQml(QObject *parent = 0);
  CameraQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Camera* camera();

  static CameraQtQml* fromCamera(Camera *camera, QObject *parent = 0);
};

}

#endif // _OSG_CAMERA_QTQML_
