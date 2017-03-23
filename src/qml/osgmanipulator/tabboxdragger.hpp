#ifndef _OSGMANIPULATOR_TABBOXDRAGGER_QTQML_
#define _OSGMANIPULATOR_TABBOXDRAGGER_QTQML_ 1

#include <osgManipulator/CompositeDraggerQtQml>

#include <QtGui/QColor>

namespace osgManipulator {

class TabBoxDragger;

class OSGQTQML_EXPORT TabBoxDraggerQtQml : public CompositeDraggerQtQml
{
  Q_OBJECT

  Q_PROPERTY(QColor planeColor READ getPlaneColor WRITE setPlaneColor NOTIFY planeColorChanged)

public:
  class Index;

  TabBoxDraggerQtQml(QObject *parent = 0);
  TabBoxDraggerQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QColor getPlaneColor() const;
  Q_INVOKABLE void setPlaneColor(const QColor &color);

  TabBoxDragger* asTabBoxDragger();

  static TabBoxDraggerQtQml* fromTabBoxDragger(TabBoxDragger *dragger, QObject *parent = 0);

Q_SIGNALS:
  void planeColorChanged(const QColor &color) const;
};

}

#endif // _OSGMANIPULATOR_TABBOXDRAGGER_QTQML_
