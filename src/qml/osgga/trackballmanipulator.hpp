#ifndef _OSGGA_TRACKBALLMANIPULATOR_QTQML_
#define _OSGGA_TRACKBALLMANIPULATOR_QTQML_ 1

#include <osgGA/OrbitManipulatorQtQml>

namespace osgGA {

class TrackballManipulator;

class OSGQTQML_EXPORT TrackballManipulatorQtQml : public OrbitManipulatorQtQml
{
  Q_OBJECT

public:
  class Index;

  TrackballManipulatorQtQml(QObject *parent = 0);
  TrackballManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  TrackballManipulator* trackballManipulator();

  static TrackballManipulatorQtQml* fromTrackballManipulator(TrackballManipulator *trackballManipulator, QObject *parent = 0);
};

}

#endif // _OSGGA_TRACKBALLMANIPULATOR_QTQML_
