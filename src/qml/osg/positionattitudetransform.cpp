#include "positionattitudetransform.hpp"
#include "positionattitudetransformindex.hpp"

#include <osg/PositionAttitudeTransform>

#include <QDebug>

namespace osg {

PositionAttitudeTransformQtQml::Index::Index(PositionAttitudeTransform *transform) :
    GroupQtQml::Index(transform),
    qthis(0)
{
    othis = transform;
}

void PositionAttitudeTransformQtQml::Index::classBegin()
{
    if(!othis) othis = new PositionAttitudeTransform();
    GroupQtQml::Index::othis = othis;
    GroupQtQml::Index::qthis = qthis;

    GroupQtQml::Index::classBegin();
}

void PositionAttitudeTransformQtQml::Index::setPosition(const QVector3D &pos)
{
    osg::Vec3d a = osgQt::vec3d(pos);

    if(othis->getPosition() == a) return;

    othis->setPosition(a);

    emit qthis->positionChanged(pos);
}

void PositionAttitudeTransformQtQml::Index::setAttitude(const QQuaternion &quat)
{
    osg::Quat a = osgQt::quat(quat);

    if(othis->getAttitude() == a) return;

    othis->setAttitude(a);

    emit qthis->attitudeChanged(quat);
}

void PositionAttitudeTransformQtQml::Index::setScale(const QVector3D &scale)
{
    osg::Vec3d a = osgQt::vec3d(scale);

    if(othis->getScale() == a) return;

    othis->setScale(a);

    emit qthis->scaleChanged(scale);
}

void PositionAttitudeTransformQtQml::Index::setPivotPoint(const QVector3D &pivot)
{
    osg::Vec3d a = osgQt::vec3d(pivot);

    if(othis->getPivotPoint() == a) return;

    othis->setPivotPoint(a);

    emit qthis->pivotPointChanged(pivot);
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    GroupQtQml::classBegin();
}

QVector3D PositionAttitudeTransformQtQml::getPosition() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getPosition());
}

void PositionAttitudeTransformQtQml::setPosition(const QVector3D &pos)
{
    static_cast<Index*>(i)->setPosition(pos);
}

QQuaternion PositionAttitudeTransformQtQml::getAttitude() const
{
    return osgQt::qQuaternion(static_cast<Index*>(i)->othis->getAttitude());
}

void PositionAttitudeTransformQtQml::setAttitude(const QQuaternion &quat)
{
    static_cast<Index*>(i)->setAttitude(quat);
}

QVector3D PositionAttitudeTransformQtQml::getScale() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getScale());
}

void PositionAttitudeTransformQtQml::setScale(const QVector3D &scale)
{
    static_cast<Index*>(i)->setScale(scale);
}

QVector3D PositionAttitudeTransformQtQml::getPivotPoint() const
{
    return osgQt::qVector3D(static_cast<Index*>(i)->othis->getPivotPoint());
}

void PositionAttitudeTransformQtQml::setPivotPoint(const QVector3D &pivot)
{
    static_cast<Index*>(i)->setPivotPoint(pivot);
}

PositionAttitudeTransform *PositionAttitudeTransformQtQml::asPositionAttitudeTransform()
{
    return static_cast<Index*>(i)->othis;
}

PositionAttitudeTransformQtQml *PositionAttitudeTransformQtQml::fromPositionAttitudeTransform(PositionAttitudeTransform *transform, QObject *parent)
{
    if(!transform) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(transform))
    {
        return static_cast<Index*>(index)->qthis;
    }

    PositionAttitudeTransformQtQml *result = new PositionAttitudeTransformQtQml(new Index(transform), parent);
    result->classBegin();
    return result;
}

}
