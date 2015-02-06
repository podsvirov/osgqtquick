#ifndef _OSGGA_ORBITMANIPULATOR_QTQML_
#define _OSGGA_ORBITMANIPULATOR_QTQML_ 1

#include <osgGA/StandardManipulatorQtQml>

namespace osgGA {

class OrbitManipulator;

class OSGQTQML_EXPORT OrbitManipulatorQtQml : public StandardManipulatorQtQml
{
  Q_OBJECT

public:
  class Index;

  OrbitManipulatorQtQml(QObject *parent = 0);
  OrbitManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  OrbitManipulator* orbitManipulator();

  static OrbitManipulatorQtQml* fromOrbitManipulator(OrbitManipulator *orbitManipulator, QObject *parent = 0);
};

}

#endif // _OSGGA_ORBITMANIPULATOR_QTQML_
