#include "cylinder.hpp"
#include "cylinderindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QDebug>

/*!
   \qmltype Cylinder
   \inherits Shape
   \inqmlmodule osg
   \brief Cylinder shape
 */

namespace osg {

CylinderQtQml::Index::Index(Cylinder *box) :
    ShapeQtQml::Index(box),
    qthis(0)
{
    othis = box;
}

void CylinderQtQml::Index::classBegin()
{
    if(!othis) othis = new Cylinder();
    ShapeQtQml::Index::othis = othis;
    ShapeQtQml::Index::qthis = qthis;

    ShapeQtQml::Index::classBegin();
}

void CylinderQtQml::Index::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(othis->getCenter() == a) return;

    othis->setCenter(a);

    emit qthis->centerChanged(center);
}

void CylinderQtQml::Index::setRadius(float radius)
{
    if(othis->getRadius() == radius) return;

    othis->setRadius(radius);

    emit qthis->radiusChanged(radius);
}

void CylinderQtQml::Index::setHeight(float height)
{
    if(othis->getHeight() == height) return;

    othis->setHeight(height);

    emit qthis->heightChanged(height);
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Cylinder::center

   Center of shape
 */

QVector3D CylinderQtQml::getCenter() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getCenter());
}

void CylinderQtQml::setCenter(const QVector3D &halfLengths)
{
    static_cast<Index*>(i)->setCenter(halfLengths);
}

/*!
   \qmlproperty float osg::Cylinder::radius

   Cylinder radius
 */

float CylinderQtQml::getRadius() const
{
    return static_cast<Index*>(i)->othis->getRadius();
}

void CylinderQtQml::setRadius(float radius)
{
    static_cast<Index*>(i)->setRadius(radius);
}

/*!
   \qmlproperty float osg::Cylinder::height

   Cylinder height
 */

float CylinderQtQml::getHeight() const
{
    return static_cast<Index*>(i)->othis->getHeight();
}

void CylinderQtQml::setHeight(float height)
{
    static_cast<Index*>(i)->setHeight(height);
}

Cylinder *CylinderQtQml::cylinder()
{
    return static_cast<Index*>(i)->othis;
}

CylinderQtQml *CylinderQtQml::fromCylinder(Cylinder *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new CylinderQtQml(new Index(drawable), parent);
}

}
