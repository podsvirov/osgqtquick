#include "sphere.hpp"
#include "sphereindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QtCore/QDebug>

/*!
   \qmltype Sphere
   \inherits Shape
   \inqmlmodule osg
   \brief Sphere shape
 */

namespace osg {

SphereQtQml::Index::Index(Sphere *box) :
    ShapeQtQml::Index(box)
{
}

void SphereQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Sphere);

    ShapeQtQml::Index::classBegin();
}

void SphereQtQml::Index::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(o(this)->getCenter() == a) return;

    o(this)->setCenter(a);

    emit q(this)->centerChanged(center);
}

void SphereQtQml::Index::setRadius(float radius)
{
    if(o(this)->getRadius() == radius) return;

    o(this)->setRadius(radius);

    emit q(this)->radiusChanged(radius);
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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Sphere::center

   Center of shape
 */

QVector3D SphereQtQml::getCenter() const
{
    return osgQt::qVector3D(o(this)->getCenter());
}

void SphereQtQml::setCenter(const QVector3D &halfLengths)
{
    i(this)->setCenter(halfLengths);
}

/*!
   \qmlproperty float osg::Sphere::radius

   Sphere radius
 */

float SphereQtQml::getRadius() const
{
    return o(this)->getRadius();
}

void SphereQtQml::setRadius(float radius)
{
    i(this)->setRadius(radius);
}

Sphere *SphereQtQml::sphere()
{
    return o(this);
}

SphereQtQml *SphereQtQml::fromSphere(Sphere *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<SphereQtQml*>(index->qtObject());
    }

    SphereQtQml *result = new SphereQtQml(new Index(drawable), parent);
    result->classBegin();
    return result;
}

}
