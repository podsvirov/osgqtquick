#ifndef _OSGGA_STANDARDMANIPULATOR_QTQML_
#define _OSGGA_STANDARDMANIPULATOR_QTQML_ 1

#include <osgGA/CameraManipulatorQtQml>

namespace osgGA {

class StandardManipulator;

class OSGQTQML_EXPORT StandardManipulatorQtQml : public CameraManipulatorQtQml
{
  Q_OBJECT

public:
  class Index;

  StandardManipulatorQtQml(QObject *parent = 0);
  StandardManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  StandardManipulator* standardManipulator();

  static StandardManipulatorQtQml* fromStandardManipulator(StandardManipulator *manipulator, QObject *parent = 0);
};

}

#endif // _OSGGA_STANDARDMANIPULATOR_QTQML_
