#include "positionattitudetransform.hpp"
#include "positionattitudetransformindex.hpp"

#include <osg/PositionAttitudeTransform>

#include <QDebug>

/*!
   \qmltype PositionAttitudeTransform
   \inherits Transform
   \inqmlmodule osg
   \brief Transform via vector and quaternion
 */

namespace osg {

PositionAttitudeTransformQtQml::Index::Index(PositionAttitudeTransform *transform) :
    GroupQtQml::Index(transform)
{
}

void PositionAttitudeTransformQtQml::Index::classBegin()
{
    if(!o(this)) setO(new PositionAttitudeTransform);

    GroupQtQml::Index::classBegin();
}

void PositionAttitudeTransformQtQml::Index::setPosition(const QVector3D &pos)
{
    osg::Vec3d a = osgQt::vec3d(pos);

    if(o(this)->getPosition() == a) return;

    o(this)->setPosition(a);

    emit q(this)->positionChanged(pos);
}

void PositionAttitudeTransformQtQml::Index::setAttitude(const QQuaternion &quat)
{
    osg::Quat a = osgQt::quat(quat);

    if(o(this)->getAttitude() == a) return;

    o(this)->setAttitude(a);

    emit q(this)->attitudeChanged(quat);
}

void PositionAttitudeTransformQtQml::Index::setScale(const QVector3D &scale)
{
    osg::Vec3d a = osgQt::vec3d(scale);

    if(o(this)->getScale() == a) return;

    o(this)->setScale(a);

    emit q(this)->scaleChanged(scale);
}

void PositionAttitudeTransformQtQml::Index::setPivotPoint(const QVector3D &pivot)
{
    osg::Vec3d a = osgQt::vec3d(pivot);

    if(o(this)->getPivotPoint() == a) return;

    o(this)->setPivotPoint(a);

    emit q(this)->pivotPointChanged(pivot);
}

PositionAttitudeTransformQtQml::PositionAttitudeTransformQtQml(QObject *parent) :
  GroupQtQml(parent)
{
}

PositionAttitudeTransformQtQml::PositionAttitudeTransformQtQml(PositionAttitudeTransformQtQml::Index *index, QObject *parent) :
  GroupQtQml(index, parent)
{
}

void PositionAttitudeTransformQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    GroupQtQml::classBegin();
}

/*!
   \qmlproperty vector3d osg::PositionAttitudeTransform::center

   Position
 */

QVector3D PositionAttitudeTransformQtQml::getPosition() const
{
    return osgQt::qVector3D(o(this)->getPosition());
}

void PositionAttitudeTransformQtQml::setPosition(const QVector3D &pos)
{
    i(this)->setPosition(pos);
}

/*!
   \qmlproperty quaternion osg::PositionAttitudeTransform::attitude

   Rotation
 */

QQuaternion PositionAttitudeTransformQtQml::getAttitude() const
{
    return osgQt::qQuaternion(o(this)->getAttitude());
}

void PositionAttitudeTransformQtQml::setAttitude(const QQuaternion &quat)
{
    i(this)->setAttitude(quat);
}

/*!
   \qmlproperty vector3d osg::PositionAttitudeTransform::scale

   Scale vector
 */

QVector3D PositionAttitudeTransformQtQml::getScale() const
{
    return osgQt::qVector3D(o(this)->getScale());
}

void PositionAttitudeTransformQtQml::setScale(const QVector3D &scale)
{
    i(this)->setScale(scale);
}

/*!
   \qmlproperty vector3d osg::PositionAttitudeTransform::pivotPoint

   Pivot point
 */

QVector3D PositionAttitudeTransformQtQml::getPivotPoint() const
{
    return osgQt::qVector3D(o(this)->getPivotPoint());
}

void PositionAttitudeTransformQtQml::setPivotPoint(const QVector3D &pivot)
{
    i(this)->setPivotPoint(pivot);
}

PositionAttitudeTransform *PositionAttitudeTransformQtQml::asPositionAttitudeTransform()
{
    return o(this);
}

PositionAttitudeTransformQtQml *PositionAttitudeTransformQtQml::fromPositionAttitudeTransform(PositionAttitudeTransform *transform, QObject *parent)
{
    if(!transform) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(transform))
    {
        return static_cast<PositionAttitudeTransformQtQml*>(index->qtObject());
    }

    PositionAttitudeTransformQtQml *result = new PositionAttitudeTransformQtQml(new Index(transform), parent);
    result->classBegin();
    return result;
}

}
