#ifndef _OSGMANIPULATOR_ROTATESPHEREDRAGGER_QTQML_INDEX_
#define _OSGMANIPULATOR_ROTATESPHEREDRAGGER_QTQML_INDEX_ 1

#include <osgManipulator/RotateSphereDraggerQtQml>

#include <osgManipulator/DraggerQtQmlIndex>

namespace osgManipulator {

class OSGQTQML_EXPORT RotateSphereDraggerQtQml::Index : public DraggerQtQml::Index
{
public:
    typedef RotateSphereDragger OType;
    typedef RotateSphereDraggerQtQml QType;
    friend class RotateSphereDraggerQtQml;

public:
    Index(RotateSphereDragger *dragger = 0);

    void classBegin();
};

}

#endif // _OSGMANIPULATOR_ROTATESPHEREDRAGGER_QTQML_INDEX_
