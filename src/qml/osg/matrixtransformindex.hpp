#ifndef _OSG_MATRIXTRANSFORM_QTQML_INDEX_
#define _OSG_MATRIXTRANSFORM_QTQML_INDEX_ 1

#include <osg/MatrixTransformQtQml>

#include <osg/TransformQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT MatrixTransformQtQml::Index : public TransformQtQml::Index
{
public:
    typedef MatrixTransform OType;
    typedef MatrixTransformQtQml QType;
    friend class MatrixTransformQtQml;

public:
    Index(MatrixTransform *transform = 0);

    void classBegin();
};

}

#endif // _OSG_MATRIXTRANSFORM_QTQML_INDEX_
