#ifndef _OSG_SHAPEDRAWABLE_QTQML_
#define _OSG_SHAPEDRAWABLE_QTQML_ 1

#include <osg/DrawableQtQml>

#include <osg/ShapeQtQml>

namespace osg {

class ShapeDrawable;

class OSGQTQML_EXPORT ShapeDrawableQtQml : public DrawableQtQml
{
  Q_OBJECT

  Q_PROPERTY(osg::ShapeQtQml* shape READ getShape WRITE setShape NOTIFY shapeChanged)

public:
  class Index;

  ShapeDrawableQtQml(QObject *parent = 0);
  ShapeDrawableQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE ShapeQtQml *getShape() const;
  Q_INVOKABLE void setShape(ShapeQtQml *shape);

  ShapeDrawable* shapeDrawable();

  static ShapeDrawableQtQml* fromShapeDrawable(ShapeDrawable *drawable, QObject *parent = 0);

signals:
  void shapeChanged(ShapeQtQml *shape);
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_
