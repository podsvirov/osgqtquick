#include "box.hpp"
#include "boxindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QDebug>

/*!
   \qmltype Box
   \inherits osg::Shape
   \inqmlmodule osg
   \brief Box shape
 */

namespace osg {

BoxQtQml::Index::Index(Box *box) :
    ShapeQtQml::Index(box),
    qthis(0)
{
    othis = box;
}

void BoxQtQml::Index::classBegin()
{
    if(!othis) othis = new Box();
    ShapeQtQml::Index::othis = othis;
    ShapeQtQml::Index::qthis = qthis;

    ShapeQtQml::Index::classBegin();
}

void BoxQtQml::Index::setHalfLengths(const QVector3D &halfLengths)
{
    osg::Vec3d a = osgQt::vec3d(halfLengths);

    if(othis->getHalfLengths() == a) return;

    othis->setHalfLengths(a);

    emit qthis->halfLengthsChanged(halfLengths);
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ShapeQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::Box::center

   Center of shape
 */

QVector3D BoxQtQml::getCenter() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getCenter());
}

void BoxQtQml::setCenter(const QVector3D &center)
{
    osg::Vec3d a = osgQt::vec3d(center);

    if(static_cast<Index*>(i)->othis->getCenter() == a) return;

    static_cast<Index*>(i)->othis->setCenter(a);

    emit centerChanged(center);
}

/*!
   \qmlproperty vector3d osg::Box::halfLengths

   Half lengths
 */

QVector3D BoxQtQml::getHalfLengths() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getHalfLengths());
}

void BoxQtQml::setHalfLengths(const QVector3D &halfLengths)
{
    static_cast<Index*>(i)->setHalfLengths(halfLengths);
}

/*!
   \qmlproperty quaternion osg::Box::rotation

   Shape rotation
 */

QQuaternion BoxQtQml::getRotation() const
{
    return osgQt::qQuaternion(static_cast<Index*>(i)->othis->getRotation());
}

void BoxQtQml::setRotation(const QQuaternion &quat)
{
    osg::Quat a = osgQt::quat(quat);

    if(static_cast<Index*>(i)->othis->getRotation() == a) return;

    static_cast<Index*>(i)->othis->setRotation(a);

    emit rotationChanged(quat);
}

Box *BoxQtQml::box()
{
    return static_cast<Index*>(i)->othis;
}

BoxQtQml *BoxQtQml::fromBox(Box *drawable, QObject *parent)
{
    if(!drawable) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(drawable))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new BoxQtQml(new Index(drawable), parent);
}

}
