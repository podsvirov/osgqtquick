#include "cylinder.hpp"
#include "cylinderindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QtCore/QDebug>

/*!
   \qmltype Cylinder
   \inherits Shape
   \inqmlmodule osg
   \brief Cylinder shape
 */

namespace osg {

CylinderQtQml::Index::Index(Cylinder *box) :
    ShapeQtQml::Index(box)
{
}

void CylinderQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Cylinder);

    ShapeQtQml::Index::classBegin();
}

void CylinderQtQml::Index::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(o(this)->getCenter() == a) return;

    o(this)->setCenter(a);

    emit q(this)->centerChanged(center);
}

void CylinderQtQml::Index::setRadius(float radius)
{
    if(o(this)->getRadius() == radius) return;

    o(this)->setRadius(radius);

    emit q(this)->radiusChanged(radius);
}

void CylinderQtQml::Index::setHeight(float height)
{
    if(o(this)->getHeight() == height) return;

    o(this)->setHeight(height);

    emit q(this)->heightChanged(height);
}

CylinderQtQml::CylinderQtQml(QObject *parent) :
  ShapeQtQml(parent)
{
}

CylinderQtQml::CylinderQtQml(CylinderQtQml::Index *index, QObject *parent) :
  ShapeQtQml(index, parent)
{
}

void CylinderQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Cylinder::center

   Center of shape
 */

QVector3D CylinderQtQml::getCenter() const
{
    return osgQt::qVector3D(o(this)->getCenter());
}

void CylinderQtQml::setCenter(const QVector3D &halfLengths)
{
    i(this)->setCenter(halfLengths);
}

/*!
   \qmlproperty float osg::Cylinder::radius

   Cylinder radius
 */

float CylinderQtQml::getRadius() const
{
    return o(this)->getRadius();
}

void CylinderQtQml::setRadius(float radius)
{
    i(this)->setRadius(radius);
}

/*!
   \qmlproperty float osg::Cylinder::height

   Cylinder height
 */

float CylinderQtQml::getHeight() const
{
    return o(this)->getHeight();
}

void CylinderQtQml::setHeight(float height)
{
    i(this)->setHeight(height);
}

Cylinder *CylinderQtQml::cylinder()
{
    return o(this);
}

CylinderQtQml *CylinderQtQml::fromCylinder(Cylinder *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<CylinderQtQml*>(index->qtObject());
    }

    CylinderQtQml *result = new CylinderQtQml(new Index(drawable), parent);
    result->classBegin();
    return result;
}

}
