#include "cone.hpp"
#include "coneindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QtCore/QDebug>

/*!
   \qmltype Cone
   \inherits Shape
   \inqmlmodule osg
   \brief Cone shape
 */

namespace osg {

ConeQtQml::Index::Index(Cone *box) :
    ShapeQtQml::Index(box)
{
}

void ConeQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Cone);

    ShapeQtQml::Index::classBegin();
}

void ConeQtQml::Index::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(o(this)->getCenter() == a) return;

    o(this)->setCenter(a);

    emit q(this)->centerChanged(center);
}

void ConeQtQml::Index::setRadius(float radius)
{
    if(o(this)->getRadius() == radius) return;

    o(this)->setRadius(radius);

    emit q(this)->radiusChanged(radius);
}

void ConeQtQml::Index::setHeight(float height)
{
    if(o(this)->getHeight() == height) return;

    o(this)->setHeight(height);

    emit q(this)->heightChanged(height);
}

ConeQtQml::ConeQtQml(QObject *parent) :
  ShapeQtQml(parent)
{
}

ConeQtQml::ConeQtQml(ConeQtQml::Index *index, QObject *parent) :
  ShapeQtQml(index, parent)
{
}

void ConeQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Cone::center

   Center of shape
 */

QVector3D ConeQtQml::getCenter() const
{
    return osgQt::qVector3D(o(this)->getCenter());
}

void ConeQtQml::setCenter(const QVector3D &halfLengths)
{
    i(this)->setCenter(halfLengths);
}

/*!
   \qmlproperty float osg::Cone::radius

   Base radius
 */

float ConeQtQml::getRadius() const
{
    return o(this)->getRadius();
}

void ConeQtQml::setRadius(float radius)
{
    i(this)->setRadius(radius);
}

/*!
   \qmlproperty float osg::Cone::height

   Cone height
 */

float ConeQtQml::getHeight() const
{
    return o(this)->getHeight();
}

void ConeQtQml::setHeight(float height)
{
    i(this)->setHeight(height);
}

Cone *ConeQtQml::cone()
{
    return o(this);
}

ConeQtQml *ConeQtQml::fromCone(Cone *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<ConeQtQml*>(index->qtObject());
    }

    ConeQtQml *result = new ConeQtQml(new Index(drawable), parent);
    result->classBegin();
    return result;
}

}
