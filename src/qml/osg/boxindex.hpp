#ifndef _OSG_BOX_QTQML_INDEX_
#define _OSG_BOX_QTQML_INDEX_ 1

#include <osg/BoxQtQml>

#include <osg/ShapeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT BoxQtQml::Index : public ShapeQtQml::Index
{
public:
    typedef Box OType;
    typedef BoxQtQml QType;
    friend class BoxQtQml;

public:
    Index(Box *o = 0);

    void classBegin();

    void setHalfLengths(const QVector3D &halfLengths);
};

}

#endif // _OSG_BOX_QTQML_INDEX_
