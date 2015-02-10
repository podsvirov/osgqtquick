#ifndef _OSG_GROUP_QTQML_
#define _OSG_GROUP_QTQML_ 1

#include <osg/NodeQtQml>

namespace osg {

class Group;

class OSGQTQML_EXPORT GroupQtQml : public NodeQtQml
{
  Q_OBJECT

  Q_PROPERTY(int numChildren READ getNumChildren NOTIFY numChildrenChanged)

public:
  class Index;

  GroupQtQml(QObject *parent = 0);
  GroupQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE bool addChild(NodeQtQml *child);
  Q_INVOKABLE bool removeChild(NodeQtQml *child);

  Q_INVOKABLE int getNumChildren() const;

  Q_INVOKABLE bool removeChildren(int pos, int numChildrenToRemove);

  Group* group();

  static GroupQtQml* fromGroup(Group *group, QObject *parent = 0);

signals:
  void numChildrenChanged(int num);
};

}

#endif // _OSG_GROUP_QTQML_
