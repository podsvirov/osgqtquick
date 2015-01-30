#include "view.hpp"
#include "viewindex.hpp"

#include <osgQtQml/Index>

#include <osgViewer/View>

namespace osgViewer {

ViewQtQuick::Index::Index(View *o) :
    osgQtQml::Index(o ? o : new osgViewer::View())
{
}

osg::NodeQtQml *ViewQtQuick::Index::getSceneData()
{
    // TODO: Implement

    //View *that = static_cast<View*>(osgObject());

    //return osg::NodeQtQml::fromNode(that->getSceneData(), qtObject());

    return 0;
}

void ViewQtQuick::Index::setSeceneData(osg::NodeQtQml *node)
{
    osg::Node *osgNode = static_cast<osg::Node*>(node->index()->osgObject());

    if(!osgNode) return;

    // TODO: Implement

    //View *that = static_cast<osg::Group*>(osgObject());

    //that->setSceneData(osgNode);
}

osg::NodeQtQml *ViewQtQuick::getSceneData()
{

}

void ViewQtQuick::setSeceneData(osg::NodeQtQml *node)
{

}

ViewQtQuick::ViewQtQuick(QQuickItem *parent) :
  osgQtQuick::Object(new ViewQtQuick::Index(), parent)
{    
}

ViewQtQuick::ViewQtQuick(ViewQtQuick::Index *index, QQuickItem *parent) :
  osgQtQuick::Object(index, parent)
{
}

}
