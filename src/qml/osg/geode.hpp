#ifndef _OSG_GEODE_QTQML_
#define _OSG_GEODE_QTQML_ 1

#include <osg/GroupQtQml>
#include <osg/DrawableQtQml>

#include <QQmlListProperty>

namespace osg {

class Geode;

class OSGQTQML_EXPORT GeodeQtQml : public GroupQtQml
{
  Q_OBJECT

  Q_PROPERTY(int numDrawables READ getNumDrawables NOTIFY numDrawablesChanged)
  Q_PROPERTY(QQmlListProperty<osg::DrawableQtQml> drawables READ drawables NOTIFY numDrawablesChanged)

  Q_CLASSINFO("DefaultProperty", "drawables")

public:
  class Index;

  GeodeQtQml(QObject *parent = 0);
  GeodeQtQml(Index *, QObject *parent = 0);

  void classBegin();
  void componentComplete();

  Q_INVOKABLE bool addDrawable(DrawableQtQml *drawable);
  Q_INVOKABLE bool removeDrawable(DrawableQtQml *drawable);
  Q_INVOKABLE bool removeDrawables(int pos, int numDrawablesToRemove = 1);
  Q_INVOKABLE int getNumDrawables() const;
  Q_INVOKABLE osg::DrawableQtQml* getDrawable(int pos);

  QQmlListProperty<DrawableQtQml> drawables();

  Geode* geode();

  static GeodeQtQml* fromGeode(Geode *geode, QObject *parent = 0);

signals:
  void numDrawablesChanged(int num);

protected:
  static int drawablesCount(QQmlListProperty<osg::DrawableQtQml> *list);
  static DrawableQtQml* drawablesAt(QQmlListProperty<osg::DrawableQtQml> *list, int index);
  static void drawablesAppend(QQmlListProperty<osg::DrawableQtQml> *list, osg::DrawableQtQml *drawable);
  static void drawablesClear(QQmlListProperty<osg::DrawableQtQml> *list);
};

}

#endif // _OSG_GEODE_QTQML_
