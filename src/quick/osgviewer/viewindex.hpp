#ifndef _OSGVIEWER_VIEW_QTQUICK_INDEX_
#define _OSGVIEWER_VIEW_QTQUICK_INDEX_ 1

#include <osgQtQml/Index>

#include <osgViewer/ViewQtQuick>

namespace osgViewer {

class OSGQTQUICK_EXPORT ViewQtQuick::Index : public osgQtQml::Index
{
    friend class ViewQtQuick;

public:
    Index(View *o = 0);

    osg::NodeQtQml* getSceneData();
    void setSceneData(osg::NodeQtQml *node);

    void classBegin();

private:
    View *othis;
    ViewQtQuick *qthis;
};

}

#endif // _OSGVIEWER_VIEW_QTQUICK_INDEX_
