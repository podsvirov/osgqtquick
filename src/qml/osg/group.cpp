#include "group.hpp"
#include "groupindex.hpp"

#include <osgQtQml/Index>

#include <osg/Group>

#include <QDebug>

/*!
   \qmltype Group
   \inherits Node
   \inqmlmodule osg
   \brief General group node which maintains a list of children
 */

namespace osg {

GroupQtQml::Index::Index(Group *group) :
    NodeQtQml::Index(group),
    qthis(0),
    _completeInfo(0)
{
  othis = group;
}

GroupQtQml::Index::~Index()
{
  if(_completeInfo) delete _completeInfo;
}

void GroupQtQml::Index::classBegin()
{
    if(!othis) othis = new Group();
    NodeQtQml::Index::othis = othis;
    NodeQtQml::Index::qthis = qthis;

    NodeQtQml::Index::classBegin();
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

void GroupQtQml::componentComplete()
{
  NodeQtQml::componentComplete();

  if(Index::CompleteInfo *info = static_cast<Index*>(i)->_completeInfo)
    {
      for(QList<NodeQtQml*>::iterator it = info->child.begin();
          it != info->child.end(); ++it)
        {
          addChild(*it);
        }
    }
}

/*!
   \qmlmethod osg::Group::addChild(Node child)

   Add \l {Node} to \l {Group}.
 */

bool GroupQtQml::addChild(NodeQtQml *child)
{
  if (!isComplete())
    {
      static_cast<Index*>(i)->info()->child.append(child);
      return true;
    }
  else if (static_cast<GroupQtQml::Index*>(i)->othis->addChild(
        child->node()))
    {
      emit numChildrenChanged(getNumChildren());
      return true;
    }

  return false;
}

/*!
   \qmlmethod osg::Group::removeChild(osg::Node child)

   Remove \l {Node} from \l {Group}.
 */

bool GroupQtQml::removeChild(NodeQtQml *child)
{
    if (static_cast<GroupQtQml::Index*>(i)->othis->removeChild(
                child->node()))
    {
        emit numChildrenChanged(getNumChildren());
        return true;
    }

    return false;
}

bool GroupQtQml::removeChild(unsigned int pos, unsigned int numChildrenToRemove)
{
  if (static_cast<GroupQtQml::Index*>(i)->othis->removeChild(pos, numChildrenToRemove))
  {
      emit numChildrenChanged(getNumChildren());
      return true;
  }

  return false;
}

bool GroupQtQml::removeChildren(int pos, int numChildrenToRemove)
{
    if (pos < 0 || numChildrenToRemove < 0) return false;

    return static_cast<Index*>(i)->othis->removeChildren(
                static_cast<unsigned int>(pos),
                static_cast<unsigned int>(numChildrenToRemove));
}

/*!
   \qmlproperty int osg::Group::numChildren

   Number of children nodes
 */

int GroupQtQml::getNumChildren() const
{
    return static_cast<Index*>(i)->othis->getNumChildren();
}

NodeQtQml *GroupQtQml::getChild(int i)
{
  return osg::NodeQtQml::fromNode(static_cast<Index*>(this->i)->othis->getChild(i));
}

/*!
   \qmlproperty list<osg::Node> osg::Group::child

   List of children nodes
 */

QQmlListProperty<NodeQtQml> GroupQtQml::children()
{
  return QQmlListProperty<osg::NodeQtQml>(this, (void*)0,
                                          GroupQtQml::childrenAppend,
                                          GroupQtQml::childrenCount,
                                          GroupQtQml::childrenAt,
                                          GroupQtQml::childrenClear);
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

int GroupQtQml::childrenCount(QQmlListProperty<NodeQtQml> *list)
{
  return static_cast<GroupQtQml*>(list->object)->getNumChildren();
}

NodeQtQml* GroupQtQml::childrenAt(QQmlListProperty<NodeQtQml> *list, int index)
{
  return static_cast<GroupQtQml*>(list->object)->getChild(index);
}

void GroupQtQml::childrenAppend(QQmlListProperty<NodeQtQml> *list, NodeQtQml *child)
{
  static_cast<GroupQtQml*>(list->object)->addChild(child);
}

void GroupQtQml::childrenClear(QQmlListProperty<NodeQtQml> *list)
{
  static_cast<GroupQtQml*>(list->object)->removeChild(0, childrenCount(list));
}

}
