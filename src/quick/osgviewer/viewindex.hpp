#ifndef _OSGVIEWER_VIEW_QTQUICK_INDEX_
#define _OSGVIEWER_VIEW_QTQUICK_INDEX_ 1

#include <osgQtQml/Index>

#include <osgViewer/ViewQtQuick>

namespace osgViewer {

class View;

class OSGQTQUICK_EXPORT ViewQtQuick::Index : public osgQtQml::Index
{
public:
    Index(View *o = 0);

    osg::NodeQtQml* getSceneData();
    void setSeceneData(osg::NodeQtQml *node);
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_INDEX_
