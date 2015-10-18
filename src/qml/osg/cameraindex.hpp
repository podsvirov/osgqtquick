#ifndef _OSG_CAMERA_QTQML_INDEX_
#define _OSG_CAMERA_QTQML_INDEX_ 1

#include <osg/CameraQtQml>

#include <osg/TransformQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT CameraQtQml::Index : public TransformQtQml::Index
{
public:
    typedef Camera OType;
    typedef CameraQtQml QType;
    friend class CameraQtQml;

public:
    Index(Camera *camera = 0);

    void classBegin();

    void setClearColor(const QColor &color);
    void setNearFarRatio(const double ratio);
};

}

#endif // _OSG_CAMERA_QTQML_INDEX_
