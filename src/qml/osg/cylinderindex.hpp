#ifndef _OSG_CYLINDER_QTQML_INDEX_
#define _OSG_CYLINDER_QTQML_INDEX_ 1

#include <osg/CylinderQtQml>

#include <osg/ShapeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT CylinderQtQml::Index : public ShapeQtQml::Index
{
public:
    typedef Cylinder OType;
    typedef CylinderQtQml QType;
    friend class CylinderQtQml;

public:
    Index(Cylinder *o = 0);

    void classBegin();

    void setCenter(const QVector3D &center);
    void setRadius(float radius);
    void setHeight(float height);
};

}

#endif // _OSG_CYLINDER_QTQML_INDEX_
