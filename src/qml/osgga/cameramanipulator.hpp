#ifndef _OSGGA_CAMERAMANIPULATOR_QTQML_
#define _OSGGA_CAMERAMANIPULATOR_QTQML_ 1

#include <osg/ObjectQtQml>

#include <QVector3D>

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

  Q_INVOKABLE void setHomePosition(const QVector3D &eye,
                                   const QVector3D &center,
                                   const QVector3D &up,
                                   bool autoComputeHomePosition = false);

  Q_INVOKABLE void home(qreal duration = 0.0);

  CameraManipulator* cameraManipulator();

  static CameraManipulatorQtQml* fromCameraManipulator(CameraManipulator *cameraManipulator, QObject *parent = 0);

protected:
  template<typename T, typename O = typename T::Index::OType>
  O* o(T *p);

  template<typename T, typename O = typename T::Index::OType>
  const O* o(const T *p) const;
};

template<typename T, typename O>
inline O* CameraManipulatorQtQml::o(T *p)
{
    return static_cast<O*>(i(p)->othis);
}

template<typename T, typename O>
inline const O* CameraManipulatorQtQml::o(const T *p) const
{
    return static_cast<O*>(i(p)->othis);
}

}

#endif // _OSGGA_CAMERAMANIPULATOR_QTQML_
