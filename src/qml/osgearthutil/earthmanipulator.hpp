#ifndef _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_
#define _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_ 1

#include <osgGA/CameraManipulatorQtQml>

namespace osgEarth { namespace Util {

class EarthManipulator;

class OSGQTQML_EXPORT EarthManipulatorQtQml : public osgGA::CameraManipulatorQtQml
{
  Q_OBJECT

public:
  class Index;

  EarthManipulatorQtQml(QObject *parent = 0);
  EarthManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  EarthManipulator* earthManipulator();

  static EarthManipulatorQtQml* fromEarthManipulator(EarthManipulator *earthManipulator, QObject *parent = 0);
};

} }

#endif // _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_
