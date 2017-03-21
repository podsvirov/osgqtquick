#ifndef _OSGMANIPULATOR_COMPOSITEDRAGGER_QTQML_
#define _OSGMANIPULATOR_COMPOSITEDRAGGER_QTQML_ 1

#include <osgManipulator/DraggerQtQml>

#include <QtGui/QColor>

namespace osgManipulator {

class CompositeDragger;

class OSGQTQML_EXPORT CompositeDraggerQtQml : public DraggerQtQml
{
  Q_OBJECT

  Q_PROPERTY(int numDraggers READ getNumDraggers NOTIFY numDraggersChanged)
  Q_PROPERTY(QQmlListProperty<osgManipulator::DraggerQtQml> draggers READ draggers NOTIFY numDraggersChanged)

  Q_CLASSINFO("DefaultProperty", "draggers")

public:
  class Index;

  CompositeDraggerQtQml(QObject *parent = 0);
  CompositeDraggerQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE bool addDragger(DraggerQtQml *dragger);
  Q_INVOKABLE bool removeDragger(DraggerQtQml *dragger);
  Q_INVOKABLE int getNumDraggers() const;
  Q_INVOKABLE DraggerQtQml* getDragger(int i);

  QQmlListProperty<DraggerQtQml> draggers();

  CompositeDragger* asCompositeDragger();

  static CompositeDraggerQtQml* fromCompositeDragger(CompositeDragger *dragger, QObject *parent = 0);

Q_SIGNALS:
  void numDraggersChanged(int num);

protected:
  static int draggersCount(QQmlListProperty<DraggerQtQml> *list);
  static DraggerQtQml* draggerAt(QQmlListProperty<DraggerQtQml> *list, int index);
  static void draggerAppend(QQmlListProperty<DraggerQtQml> *list, DraggerQtQml *dragger);
  static void draggersClear(QQmlListProperty<DraggerQtQml> *list);
};

}

#endif // _OSGMANIPULATOR_COMPOSITEDRAGGER_QTQML_
