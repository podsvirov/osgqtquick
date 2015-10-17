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
  template<typename T>
  typename T::Index::OType* o(T *p);

  template<typename T>
  const typename T::Index::OType* o(const T *p) const;
};

template<typename T>
inline typename T::Index::OType* CameraManipulatorQtQml::o(T *p)
{
    return static_cast<typename T::Index::OType*>(i(p)->othis);
}

template<typename T>
inline const typename T::Index::OType* CameraManipulatorQtQml::o(const T *p) const
{
    return static_cast<typename T::Index::OType*>(i(p)->othis);
}

}

#endif // _OSGGA_CAMERAMANIPULATOR_QTQML_
