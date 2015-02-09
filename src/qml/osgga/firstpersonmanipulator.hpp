#ifndef _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_
#define _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_ 1

#include <osgGA/StandardManipulatorQtQml>

namespace osgGA {

class FirstPersonManipulator;

class OSGQTQML_EXPORT FirstPersonManipulatorQtQml : public StandardManipulatorQtQml
{
  Q_OBJECT

public:
  class Index;

  FirstPersonManipulatorQtQml(QObject *parent = 0);
  FirstPersonManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  FirstPersonManipulator* firstPersonManipulator();

  static FirstPersonManipulatorQtQml* fromFirstPersonManipulator(FirstPersonManipulator *manipulator, QObject *parent = 0);
};

}

#endif // _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_
