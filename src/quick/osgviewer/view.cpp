#include "view.hpp"
#include "viewindex.hpp"

#include <osgViewer/View>

namespace osgViewer {

ViewQtQuick::Index::Index(View *view) :
    osgQtQuick::Index(view)
{
    othis = view;
}

osg::NodeQtQml *ViewQtQuick::Index::getSceneData()
{
    return osg::NodeQtQml::fromNode(othis->getSceneData(), qthis);
}

void ViewQtQuick::Index::setSceneData(osg::NodeQtQml *node)
{
    othis->setSceneData(node->node());
}

void ViewQtQuick::Index::classBegin()
{
    if(!othis) othis = new View();
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

ViewQtQuick *ViewQtQuick::fromView(View *view, QQuickItem *parent)
{
    if(!view) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(view))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new ViewQtQuick(new Index(view), parent);
}

osg::NodeQtQml *ViewQtQuick::getSceneData()
{
    return static_cast<Index*>(i)->getSceneData();
}

void ViewQtQuick::setSceneData(osg::NodeQtQml *node)
{
    static_cast<Index*>(i)->setSceneData(node);
}

ViewQtQuick::ViewQtQuick(QQuickItem *parent) :
  osgQtQuick::Object(parent)
{    
}

ViewQtQuick::ViewQtQuick(ViewQtQuick::Index *index, QQuickItem *parent) :
  osgQtQuick::Object(index, parent)
{
}

void ViewQtQuick::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQuick::Object::classBegin();
}

}
