#ifndef _OSG_CONE_QTQML_INDEX_
#define _OSG_CONE_QTQML_INDEX_ 1

#include <osg/ConeQtQml>

#include <osg/ShapeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT ConeQtQml::Index : public ShapeQtQml::Index
{
public:
    typedef Cone OType;
    typedef ConeQtQml QType;
    friend class ConeQtQml;

public:
    Index(Cone *o = 0);

    void classBegin();

    void setCenter(const QVector3D &center);
    void setRadius(float radius);
    void setHeight(float height);
};

}

#endif // _OSG_CONE_QTQML_INDEX_
