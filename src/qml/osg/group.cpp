#include "group.hpp"
#include "groupindex.hpp"

#include <osgQtQml/Index>

#include <osg/Group>

#include <QDebug>

namespace osg {

GroupQtQml::Index::Index(Group *group) :
    NodeQtQml::Index(group),
    qthis(0)
{
    othis = group;
}

void GroupQtQml::Index::classBegin()
{
    if(!othis) othis = new Group();
    NodeQtQml::Index::othis = othis;
    NodeQtQml::Index::qthis = qthis;

    NodeQtQml::Index::classBegin();
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
  NodeQtQml(parent)
{
}

GroupQtQml::GroupQtQml(GroupQtQml::Index *index, QObject *parent) :
  NodeQtQml(index, parent)
{
}

void GroupQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    NodeQtQml::classBegin();
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

bool GroupQtQml::removeChildren(int pos, int numChildrenToRemove)
{
    if (pos < 0 || numChildrenToRemove < 0) return false;

    return static_cast<Index*>(i)->othis->removeChildren(
                static_cast<unsigned int>(pos),
                static_cast<unsigned int>(numChildrenToRemove));
}

Group *GroupQtQml::group()
{
    return static_cast<Index*>(i)->othis;
}

GroupQtQml *GroupQtQml::fromGroup(Group *group, QObject *parent)
{
    if(!group) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(group))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new GroupQtQml(new Index(group), parent);
}

}
