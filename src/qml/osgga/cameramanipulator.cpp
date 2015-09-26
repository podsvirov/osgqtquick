#include "cameramanipulator.hpp"
#include "cameramanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/CameraManipulator>

#include <QDebug>

/*!
   \qmltype CameraManipulator
   \inherits osg::Object
   \inqmlmodule osgGA
   \brief Uncreatable base type for all camera manipulators
 */

namespace osgGA {

CameraManipulatorQtQml::Index::Index(CameraManipulator *cameraManipulator) :
    ObjectQtQml::Index(cameraManipulator),
    qthis(0)
{
    othis = cameraManipulator;
}

void CameraManipulatorQtQml::Index::classBegin()
{
    ObjectQtQml::Index::othis = othis;
    ObjectQtQml::Index::qthis = qthis;

    ObjectQtQml::Index::classBegin();
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

void CameraManipulatorQtQml::setHomePosition(const QVector3D &eye, const QVector3D &center, const QVector3D &up, bool autoComputeHomePosition)
{
    static_cast<Index*>(i)->othis->setHomePosition(
                osgQt::vec3d(eye),
                osgQt::vec3d(center),
                osgQt::vec3d(up),
                autoComputeHomePosition);
}

void CameraManipulatorQtQml::home(qreal duration)
{
    static_cast<Index*>(i)->othis->home(static_cast<double>(duration));
}

CameraManipulator *CameraManipulatorQtQml::cameraManipulator()
{
    return static_cast<Index*>(i)->othis;
}

CameraManipulatorQtQml *CameraManipulatorQtQml::fromCameraManipulator(CameraManipulator *cameraManipulator, QObject *parent)
{
    if(!cameraManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(cameraManipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    CameraManipulatorQtQml *result = new CameraManipulatorQtQml(new Index(cameraManipulator), parent);
    result->classBegin();
    return result;
}

}
