#ifndef _OSGGA_CAMERAMANIPULATOR_QTQML_
#define _OSGGA_CAMERAMANIPULATOR_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osgGA {

class CameraManipulator;

class OSGQTQML_EXPORT CameraManipulatorQtQml : public osg::ObjectQtQml
{
  Q_OBJECT

public:
  class Index;

  CameraManipulatorQtQml(QObject *parent = 0);
  CameraManipulatorQtQml(Index *index, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE void home(qreal duration = 0.0);

  CameraManipulator* cameraManipulator();

  static CameraManipulatorQtQml* fromCameraManipulator(CameraManipulator *cameraManipulator, QObject *parent = 0);
};

}

#endif // _OSGGA_CAMERAMANIPULATOR_QTQML_
