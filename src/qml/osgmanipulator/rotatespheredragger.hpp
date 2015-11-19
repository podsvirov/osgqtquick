#ifndef _OSGMANIPULATOR_ROTATESPHEREDRAGGER_QTQML_
#define _OSGMANIPULATOR_ROTATESPHEREDRAGGER_QTQML_ 1

#include <osgManipulator/DraggerQtQml>

#include <QColor>

namespace osgManipulator {

class RotateSphereDragger;

class OSGQTQML_EXPORT RotateSphereDraggerQtQml : public DraggerQtQml
{
  Q_OBJECT

  Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
  Q_PROPERTY(QColor pickColor READ getPickColor WRITE setPickColor NOTIFY pickColorChanged)

public:
  class Index;

  RotateSphereDraggerQtQml(QObject *parent = 0);
  RotateSphereDraggerQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QColor getColor() const;
  Q_INVOKABLE void setColor(const QColor &color);

  Q_INVOKABLE QColor getPickColor() const;
  Q_INVOKABLE void setPickColor(const QColor &color);

  RotateSphereDragger* asRotateSphereDragger();

  static RotateSphereDraggerQtQml* fromRotateSphereDragger(RotateSphereDragger *dragger, QObject *parent = 0);

signals:
  void colorChanged(const QColor &color) const;
  void pickColorChanged(const QColor &color) const;
};

}

#endif // _OSGMANIPULATOR_ROTATESPHEREDRAGGER_QTQML_
