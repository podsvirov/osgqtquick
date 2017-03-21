#include "cameramanipulator.hpp"
#include "cameramanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <QtCore/QDebug>

/*!
   \qmltype CameraManipulator
   \inherits osg::Object
   \inqmlmodule osgGA
   \brief Uncreatable base type for all camera manipulators
 */

namespace osgGA {

CameraManipulatorQtQml::Index::Index(CameraManipulator *cameraManipulator) :
    ObjectQtQml::Index(cameraManipulator),
    o_ptr(0)
{
}

CameraManipulatorQtQml::CameraManipulatorQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

CameraManipulatorQtQml::CameraManipulatorQtQml(CameraManipulatorQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void CameraManipulatorQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

void CameraManipulatorQtQml::setHomePosition(const QVector3D &eye, const QVector3D &center, const QVector3D &up, bool autoComputeHomePosition)
{
    o(this)->setHomePosition(
                osgQt::vec3d(eye),
                osgQt::vec3d(center),
                osgQt::vec3d(up),
                autoComputeHomePosition);
}

void CameraManipulatorQtQml::home(qreal duration)
{
    o(this)->home(static_cast<double>(duration));
}

CameraManipulator *CameraManipulatorQtQml::cameraManipulator()
{
    return o(this);
}

CameraManipulatorQtQml *CameraManipulatorQtQml::fromCameraManipulator(CameraManipulator *cameraManipulator, QObject *parent)
{
    if(!cameraManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(cameraManipulator))
    {
        return static_cast<CameraManipulatorQtQml*>(index->qtObject());
    }

    CameraManipulatorQtQml *result = new CameraManipulatorQtQml(new Index(cameraManipulator), parent);
    result->classBegin();
    return result;
}

}
