#ifndef _OSG_SHAPEDRAWABLE_QTQML_
#define _OSG_SHAPEDRAWABLE_QTQML_ 1

#include <osg/DrawableQtQml>

#include <osg/ShapeQtQml>

#include <QtGui/QColor>

namespace osg {

class ShapeDrawable;

class OSGQTQML_EXPORT ShapeDrawableQtQml : public DrawableQtQml
{
  Q_OBJECT

  Q_PROPERTY(osg::ShapeQtQml* shape READ getShape WRITE setShape NOTIFY shapeChanged)
  Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)

public:
  class Index;

  ShapeDrawableQtQml(QObject *parent = 0);
  ShapeDrawableQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE ShapeQtQml *getShape() const;
  Q_INVOKABLE void setShape(ShapeQtQml *shape);

  Q_INVOKABLE QColor getColor() const;
  Q_INVOKABLE void setColor(const QColor &color);

  ShapeDrawable* shapeDrawable();

  static ShapeDrawableQtQml* fromShapeDrawable(ShapeDrawable *drawable, QObject *parent = 0);

Q_SIGNALS:
  void shapeChanged(ShapeQtQml *shape) const;
  void colorChanged(const QColor &color) const;
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_
