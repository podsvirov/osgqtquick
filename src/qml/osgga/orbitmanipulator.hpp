#ifndef _OSGGA_ORBITMANIPULATOR_QTQML_
#define _OSGGA_ORBITMANIPULATOR_QTQML_ 1

#include <osgGA/StandardManipulatorQtQml>

namespace osgGA {

class OrbitManipulator;

class OSGQTQML_EXPORT OrbitManipulatorQtQml : public StandardManipulatorQtQml
{
  Q_OBJECT

  Q_PROPERTY(qreal wheelZoomFactor READ getWheelZoomFactor WRITE setWheelZoomFactor NOTIFY wheelZoomFactorChanged)

public:
  class Index;

  OrbitManipulatorQtQml(QObject *parent = 0);
  OrbitManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  qreal getWheelZoomFactor() const;
  void setWheelZoomFactor(qreal wheelZoomFactor);

  OrbitManipulator* orbitManipulator();

  static OrbitManipulatorQtQml* fromOrbitManipulator(OrbitManipulator *orbitManipulator, QObject *parent = 0);

Q_SIGNALS:
  void wheelZoomFactorChanged(qreal wheelZoomFactor) const;
};

}

#endif // _OSGGA_ORBITMANIPULATOR_QTQML_
