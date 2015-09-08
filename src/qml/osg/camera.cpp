#include "camera.hpp"
#include "cameraindex.hpp"

#include <osg/Camera>

#include <QDebug>

/*!
   \qmltype Camera
   \inherits Transform
   \inqmlmodule osg
   \brief Camera
 */

namespace osg {

CameraQtQml::Index::Index(Camera *camera) :
    TransformQtQml::Index(camera),
    qthis(0)
{
    othis = camera;
}

void CameraQtQml::Index::classBegin()
{
    if(!othis) othis = new Camera();
    TransformQtQml::Index::othis = othis;
    TransformQtQml::Index::qthis = qthis;

    TransformQtQml::Index::classBegin();
}

void CameraQtQml::Index::setClearColor(const QColor &color)
{
    osg::Vec4 c = osgQt::swapColor(color);

    if(othis->getClearColor() == c) return;

    othis->setClearColor(c);

    emit qthis->clearColorChanged(color);
}

void CameraQtQml::Index::setNearFarRatio(const double ratio)
{
    if(othis->getNearFarRatio() == ratio) return;

    othis->setNearFarRatio(ratio);

    emit qthis->nearFarRatioChanged(ratio);
}

CameraQtQml::CameraQtQml(QObject *parent) :
  TransformQtQml(parent)
{
}

CameraQtQml::CameraQtQml(CameraQtQml::Index *index, QObject *parent) :
  TransformQtQml(index, parent)
{
}

void CameraQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    TransformQtQml::classBegin();
}

/*!
   \qmlproperty color osg::Camera::clearColor

   Clear color
 */

QColor CameraQtQml::getClearColor() const
{
    return osgQt::swapColor(static_cast<Index*>(i)->othis->getClearColor());
}

void CameraQtQml::setClearColor(const QColor &color)
{
    static_cast<Index*>(i)->setClearColor(color);
}

double CameraQtQml::getNearFarRatio() const
{
    return static_cast<Index*>(i)->othis->getNearFarRatio();
}

void CameraQtQml::setNearFarRatio(const double ratio)
{
    static_cast<Index*>(i)->setNearFarRatio(ratio);
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
