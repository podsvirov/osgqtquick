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
    TransformQtQml::Index(camera)
{
}

void CameraQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Camera);

    TransformQtQml::Index::classBegin();
}

void CameraQtQml::Index::setClearColor(const QColor &color)
{
    osg::Vec4 c = osgQt::swapColor(color);

    if(o(this)->getClearColor() == c) return;

    o(this)->setClearColor(c);

    emit q(this)->clearColorChanged(color);
}

void CameraQtQml::Index::setNearFarRatio(const double ratio)
{
    if(o(this)->getNearFarRatio() == ratio) return;

    o(this)->setNearFarRatio(ratio);

    emit q(this)->nearFarRatioChanged(ratio);
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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    TransformQtQml::classBegin();
}

/*!
   \qmlproperty color osg::Camera::clearColor

   Clear color
 */

QColor CameraQtQml::getClearColor() const
{
    return osgQt::swapColor(o(this)->getClearColor());
}

void CameraQtQml::setClearColor(const QColor &color)
{
    i(this)->setClearColor(color);
}

double CameraQtQml::getNearFarRatio() const
{
    return o(this)->getNearFarRatio();
}

void CameraQtQml::setNearFarRatio(const double ratio)
{
    i(this)->setNearFarRatio(ratio);
}

Camera *CameraQtQml::camera()
{
    return o(this);
}

CameraQtQml *CameraQtQml::fromCamera(Camera *camera, QObject *parent)
{
    if(!camera) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(camera))
    {
        return static_cast<CameraQtQml*>(index->qtObject());
    }

    CameraQtQml *result = new CameraQtQml(new Index(camera), parent);
    result->classBegin();
    return result;
}

}
