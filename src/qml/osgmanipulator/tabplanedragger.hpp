#ifndef _OSGMANIPULATOR_TABPLANEDRAGGER_QTQML_
#define _OSGMANIPULATOR_TABPLANEDRAGGER_QTQML_ 1

#include <osgManipulator/CompositeDraggerQtQml>

#include <QtGui/QColor>

namespace osgManipulator {

class TabPlaneDragger;

class OSGQTQML_EXPORT TabPlaneDraggerQtQml : public CompositeDraggerQtQml
{
  Q_OBJECT

  Q_PROPERTY(QColor planeColor READ getPlaneColor WRITE setPlaneColor NOTIFY planeColorChanged)

public:
  class Index;

  TabPlaneDraggerQtQml(QObject *parent = 0);
  TabPlaneDraggerQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QColor getPlaneColor() const;
  Q_INVOKABLE void setPlaneColor(const QColor &color);

  TabPlaneDragger* asTabPlaneDragger();

  static TabPlaneDraggerQtQml* fromTabPlaneDragger(TabPlaneDragger *dragger, QObject *parent = 0);

Q_SIGNALS:
  void planeColorChanged(const QColor &color) const;
};

}

#endif // _OSGMANIPULATOR_TABPLANEDRAGGER_QTQML_
