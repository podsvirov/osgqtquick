#include "cameramanipulator.hpp"
#include "cameramanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/CameraManipulator>

#include <QDebug>

namespace osgGA {

CameraManipulatorQtQml::Index::Index(CameraManipulator *cameraManipulator) :
    ObjectQtQml::Index(cameraManipulator),
    qthis(0)
{
    othis = cameraManipulator;
}

void CameraManipulatorQtQml::Index::classBegin()
{
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
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

void CameraManipulatorQtQml::home(qreal duration)
{
    qDebug() << "Home duration = " << duration;
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

    return new CameraManipulatorQtQml(new Index(cameraManipulator), parent);
}

}
