#ifndef _OSGGA_FLIGHTMANIPULATOR_QTQML_
#define _OSGGA_FLIGHTMANIPULATOR_QTQML_ 1

#include <osgGA/FirstPersonManipulatorQtQml>

namespace osgGA {

class FlightManipulator;

class OSGQTQML_EXPORT FlightManipulatorQtQml : public FirstPersonManipulatorQtQml
{
  Q_OBJECT

public:
  class Index;

  FlightManipulatorQtQml(QObject *parent = 0);
  FlightManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  FlightManipulator* flightManipulator();

  static FlightManipulatorQtQml* fromFlightManipulator(FlightManipulator *manipulator, QObject *parent = 0);
};

}

#endif // _OSGGA_FLIGHTMANIPULATOR_QTQML_
