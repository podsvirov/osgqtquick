#include "sphere.hpp"
#include "sphereindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QDebug>

/*!
   \qmltype Sphere
   \inherits osg::Shape
   \inqmlmodule osg
   \brief Sphere shape
 */

namespace osg {

SphereQtQml::Index::Index(Sphere *box) :
    ShapeQtQml::Index(box),
    qthis(0)
{
    othis = box;
}

void SphereQtQml::Index::classBegin()
{
    if(!othis) othis = new Sphere();
    ShapeQtQml::Index::othis = othis;
    ShapeQtQml::Index::qthis = qthis;

    ShapeQtQml::Index::classBegin();
}

void SphereQtQml::Index::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(othis->getCenter() == a) return;

    othis->setCenter(a);

    emit qthis->centerChanged(center);
}

void SphereQtQml::Index::setRadius(float radius)
{
    if(othis->getRadius() == radius) return;

    othis->setRadius(radius);

    emit qthis->radiusChanged(radius);
}

SphereQtQml::SphereQtQml(QObject *parent) :
  ShapeQtQml(parent)
{
}

SphereQtQml::SphereQtQml(SphereQtQml::Index *index, QObject *parent) :
  ShapeQtQml(index, parent)
{
}

void SphereQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Sphere::center

   Center of shape
 */

QVector3D SphereQtQml::getCenter() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getCenter());
}

void SphereQtQml::setCenter(const QVector3D &halfLengths)
{
    static_cast<Index*>(i)->setCenter(halfLengths);
}

/*!
   \qmlproperty float osg::Sphere::radius

   Sphere radius
 */

float SphereQtQml::getRadius() const
{
    return static_cast<Index*>(i)->othis->getRadius();
}

void SphereQtQml::setRadius(float radius)
{
    static_cast<Index*>(i)->setRadius(radius);
}

Sphere *SphereQtQml::sphere()
{
    return static_cast<Index*>(i)->othis;
}

SphereQtQml *SphereQtQml::fromSphere(Sphere *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new SphereQtQml(new Index(drawable), parent);
}

}
