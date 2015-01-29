#include "group.hpp"
#include "groupindex.hpp"

#include <osgQtQml/Index>

#include <osg/Group>

#include <QDebug>

namespace osg {

GroupQtQml::Index::Index(Group *o) :
    NodeQtQml::Index(o ? o : new osg::Group())
{
}

bool GroupQtQml::Index::addChild(NodeQtQml *child)
{
    osg::Node *osgChild = static_cast<osg::Node*>(child->index()->osgObject());

    if(!osgChild) return false;

    osg::Group *that = static_cast<osg::Group*>(osgObject());

    return that->addChild(osgChild);
}

bool GroupQtQml::Index::removeChild(NodeQtQml *child)
{
    osg::Node *osgChild = static_cast<osg::Node*>(child->index()->osgObject());

    if(!osgChild) return false;

    osg::Group *that = static_cast<osg::Group*>(osgObject());

    return that->removeChild(osgChild);
}

GroupQtQml::GroupQtQml(QObject *parent) :
  NodeQtQml(new GroupQtQml::Index(), parent)
{
}

GroupQtQml::GroupQtQml(GroupQtQml::Index *index, QObject *parent) :
  NodeQtQml(index, parent)
{

}

bool GroupQtQml::addChild(NodeQtQml *child)
{
    if (static_cast<GroupQtQml::Index*>(i)->addChild(child))
    {
        emit numChildrenChanged(getNumChildren());
        return true;
    }

    return false;
}

bool GroupQtQml::removeChild(NodeQtQml *child)
{
    if (static_cast<GroupQtQml::Index*>(i)->removeChild(child))
    {
        emit numChildrenChanged(getNumChildren());
        return true;
    }

    return false;
}

int GroupQtQml::getNumChildren() const
{
    return static_cast<osg::Group*>(i->osgObject())->getNumChildren();
}

}
