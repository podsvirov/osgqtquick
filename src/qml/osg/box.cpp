#include "box.hpp"
#include "boxindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QDebug>

/*!
   \qmltype Box
   \inherits Shape
   \inqmlmodule osg
   \brief Box shape
 */

namespace osg {

BoxQtQml::Index::Index(Box *box) :
    ShapeQtQml::Index(box)
{
}

void BoxQtQml::Index::classBegin()
{
    if(!o(this)) setO(new Box);

    ShapeQtQml::Index::classBegin();
}

void BoxQtQml::Index::setHalfLengths(const QVector3D &halfLengths)
{
    osg::Vec3d a = osgQt::vec3d(halfLengths);

    if(o(this)->getHalfLengths() == a) return;

    o(this)->setHalfLengths(a);

    emit q(this)->halfLengthsChanged(halfLengths);
}

BoxQtQml::BoxQtQml(QObject *parent) :
  ShapeQtQml(parent)
{
}

BoxQtQml::BoxQtQml(BoxQtQml::Index *index, QObject *parent) :
  ShapeQtQml(index, parent)
{
}

void BoxQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Box::center

   Center of shape
 */

QVector3D BoxQtQml::getCenter() const
{
    return osgQt::qVector3D(o(this)->getCenter());
}

void BoxQtQml::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(o(this)->getCenter() == a) return;

    o(this)->setCenter(a);

    emit centerChanged(center);
}

/*!
   \qmlproperty vector3d osg::Box::halfLengths

   Half lengths
 */

QVector3D BoxQtQml::getHalfLengths() const
{
    return osgQt::qVector3D(o(this)->getHalfLengths());
}

void BoxQtQml::setHalfLengths(const QVector3D &halfLengths)
{
    i(this)->setHalfLengths(halfLengths);
}

/*!
   \qmlproperty quaternion osg::Box::rotation

   Shape rotation
 */

QQuaternion BoxQtQml::getRotation() const
{
    return osgQt::qQuaternion(o(this)->getRotation());
}

void BoxQtQml::setRotation(const QQuaternion &quat)
{
    osg::Quat a = osgQt::quat(quat);

    if(o(this)->getRotation() == a) return;

    o(this)->setRotation(a);

    emit rotationChanged(quat);
}

Box *BoxQtQml::box()
{
    return o(this);
}

BoxQtQml *BoxQtQml::fromBox(Box *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<BoxQtQml*>(index->qtObject());
    }

    BoxQtQml *result = new BoxQtQml(new Index(drawable), parent);
    result->classBegin();
    return result;
}

}
