#ifndef _OSG_POSITIONATTITUDETRANSFORM_QTQML_INDEX_
#define _OSG_POSITIONATTITUDETRANSFORM_QTQML_INDEX_ 1

#include <osg/PositionAttitudeTransformQtQml>

#include <osg/TransformQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT PositionAttitudeTransformQtQml::Index : public GroupQtQml::Index
{
    friend class PositionAttitudeTransformQtQml;

public:
    Index(PositionAttitudeTransform *transform = 0);

    void classBegin();

    void setPosition(const QVector3D &pos);
    void setAttitude(const QQuaternion &quat);
    void setScale(const QVector3D &scale);
    void setPivotPoint(const QVector3D &pivot);

protected:
    PositionAttitudeTransform *othis;
    PositionAttitudeTransformQtQml *qthis;
};

}

#endif // _OSG_POSITIONATTITUDETRANSFORM_QTQML_INDEX_
