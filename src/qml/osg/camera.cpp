#include "camera.hpp"
#include "cameraindex.hpp"

#include <osg/Camera>

#include <QDebug>

namespace osg {

CameraQtQml::Index::Index(Camera *camera) :
    GroupQtQml::Index(camera),
    qthis(0)
{
    othis = camera;
}

void CameraQtQml::Index::classBegin()
{
    if(!othis) othis = new Camera();
    GroupQtQml::Index::othis = othis;
    GroupQtQml::Index::qthis = qthis;

    GroupQtQml::Index::classBegin();
}

void CameraQtQml::Index::setClearColor(const QColor &color)
{
    osg::Vec4 c = osgQt::swapColor(color);

    if(othis->getClearColor() == c) return;

    othis->setClearColor(c);

    emit qthis->clearColorChanged(color);
}

CameraQtQml::CameraQtQml(QObject *parent) :
  GroupQtQml(parent)
{
}

CameraQtQml::CameraQtQml(CameraQtQml::Index *index, QObject *parent) :
  GroupQtQml(index, parent)
{
}

void CameraQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    GroupQtQml::classBegin();
}

QColor CameraQtQml::getClearColor() const
{
    return osgQt::swapColor(static_cast<Index*>(i)->othis->getClearColor());
}

void CameraQtQml::setClearColor(const QColor &color)
{
    static_cast<Index*>(i)->setClearColor(color);
}

Camera *CameraQtQml::camera()
{
    return static_cast<Index*>(i)->othis;
}

CameraQtQml *CameraQtQml::fromCamera(Camera *camera, QObject *parent)
{
    if(!camera) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(camera))
    {
        return static_cast<Index*>(index)->qthis;
    }

    CameraQtQml *result = new CameraQtQml(new Index(camera), parent);
    result->classBegin();
    return result;
}

}
