#ifndef _OSG_GROUP_QTQML_
#define _OSG_GROUP_QTQML_ 1

#include <osg/NodeQtQml>

#include <QQmlListProperty>

namespace osg {

class Group;

class OSGQTQML_EXPORT GroupQtQml : public NodeQtQml
{
  Q_OBJECT

  Q_PROPERTY(int numChildren READ getNumChildren NOTIFY numChildrenChanged)
  Q_PROPERTY(QQmlListProperty<osg::NodeQtQml> child READ child NOTIFY numChildrenChanged)

  Q_CLASSINFO("DefaultProperty", "child")

public:
  class Index;

  GroupQtQml(QObject *parent = 0);
  GroupQtQml(Index *, QObject *parent = 0);

  void classBegin();
  void componentComplete();

  Q_INVOKABLE bool addChild(NodeQtQml *child);
  Q_INVOKABLE bool removeChild(NodeQtQml *child);
  Q_INVOKABLE bool removeChild(unsigned int pos, unsigned int numChildrenToRemove=1);
  Q_INVOKABLE bool removeChildren(int pos, int numChildrenToRemove);
  Q_INVOKABLE int getNumChildren() const;
  Q_INVOKABLE osg::NodeQtQml* getChild(int i);

  QQmlListProperty<NodeQtQml> child();

  Group* group();

  static GroupQtQml* fromGroup(Group *group, QObject *parent = 0);

signals:
  void numChildrenChanged(int num);

protected:
  static int childCount(QQmlListProperty<osg::NodeQtQml> *list);
  static NodeQtQml* childAt(QQmlListProperty<osg::NodeQtQml> *list, int index);
  static void childAppend(QQmlListProperty<osg::NodeQtQml> *list, osg::NodeQtQml *child);
  static void childClear(QQmlListProperty<osg::NodeQtQml> *list);
};

}

#endif // _OSG_GROUP_QTQML_
