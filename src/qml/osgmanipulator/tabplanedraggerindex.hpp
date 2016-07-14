#ifndef _OSGMANIPULATOR_TABPLANEDRAGGER_QTQML_INDEX_
#define _OSGMANIPULATOR_TABPLANEDRAGGER_QTQML_INDEX_ 1

#include <osgManipulator/TabPlaneDraggerQtQml>

#include <osgManipulator/CompositeDraggerQtQmlIndex>

namespace osgManipulator {

class OSGQTQML_EXPORT TabPlaneDraggerQtQml::Index : public CompositeDraggerQtQml::Index
{
public:
    typedef TabPlaneDragger OType;
    typedef TabPlaneDraggerQtQml QType;
    friend class TabPlaneDraggerQtQml;

public:
    Index(TabPlaneDragger *dragger = 0);

    void classBegin();

    QColor _planeColor;
};

}

#endif // _OSGMANIPULATOR_TABPLANEDRAGGER_QTQML_INDEX_
