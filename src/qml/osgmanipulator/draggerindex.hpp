#ifndef _OSGMANIPULATOR_DRAGGER_QTQML_INDEX_
#define _OSGMANIPULATOR_DRAGGER_QTQML_INDEX_ 1

#include <osgManipulator/DraggerQtQml>

#include <osg/MatrixTransformQtQmlIndex>

namespace osgManipulator {

class OSGQTQML_EXPORT DraggerQtQml::Index : public osg::MatrixTransformQtQml::Index
{
public:
    typedef Dragger OType;
    typedef DraggerQtQml QType;
    friend class DraggerQtQml;

public:
    Index(Dragger *dragger = 0);
};

}

#endif // _OSGMANIPULATOR_DRAGGER_QTQML_INDEX_
