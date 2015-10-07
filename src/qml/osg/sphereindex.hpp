#ifndef _OSG_SPHERE_QTQML_INDEX_
#define _OSG_SPHERE_QTQML_INDEX_ 1

#include <osg/SphereQtQml>

#include <osg/ShapeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT SphereQtQml::Index : public ShapeQtQml::Index
{
public:
    typedef Sphere OType;
    typedef SphereQtQml QType;
    friend class SphereQtQml;

public:
    Index(Sphere *o = 0);

    void classBegin();

    void setCenter(const QVector3D &center);
    void setRadius(float radius);
};

}

#endif // _OSG_SPHERE_QTQML_INDEX_
