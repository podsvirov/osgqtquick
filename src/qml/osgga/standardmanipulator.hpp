#ifndef _OSGGA_STANDARDMANIPULATOR_QTQML_
#define _OSGGA_STANDARDMANIPULATOR_QTQML_ 1

#include <osgGA/CameraManipulatorQtQml>

#include <osg/NodeQtQml>

namespace osgGA {

class StandardManipulator;

class OSGQTQML_EXPORT StandardManipulatorQtQml : public CameraManipulatorQtQml
{
  Q_OBJECT

  Q_PROPERTY(osg::NodeQtQml* node READ getNode WRITE setNode NOTIFY nodeChanged)

public:
  class Index;

  StandardManipulatorQtQml(QObject *parent = 0);
  StandardManipulatorQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE osg::NodeQtQml *getNode();
  Q_INVOKABLE void setNode(osg::NodeQtQml *node);

  StandardManipulator* standardManipulator();

  static StandardManipulatorQtQml* fromStandardManipulator(StandardManipulator *manipulator, QObject *parent = 0);

Q_SIGNALS:
  void nodeChanged(osg::NodeQtQml *node);
};

}

#endif // _OSGGA_STANDARDMANIPULATOR_QTQML_
