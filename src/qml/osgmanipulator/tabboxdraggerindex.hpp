#ifndef _OSGMANIPULATOR_TABBOXDRAGGER_QTQML_INDEX_
#define _OSGMANIPULATOR_TABBOXDRAGGER_QTQML_INDEX_ 1

#include <osgManipulator/TabBoxDraggerQtQml>

#include <osgManipulator/DraggerQtQmlIndex>

namespace osgManipulator {

class OSGQTQML_EXPORT TabBoxDraggerQtQml::Index : public DraggerQtQml::Index
{
public:
    typedef TabBoxDragger OType;
    typedef TabBoxDraggerQtQml QType;
    friend class TabBoxDraggerQtQml;

public:
    Index(TabBoxDragger *dragger = 0);

    void classBegin();

    QColor _planeColor;
};

}

#endif // _OSGMANIPULATOR_TABBOXDRAGGER_QTQML_INDEX_
