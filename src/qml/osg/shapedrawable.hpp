#ifndef _OSG_SHAPEDRAWABLE_QTQML_
#define _OSG_SHAPEDRAWABLE_QTQML_ 1

#include <osg/DrawableQtQml>

namespace osg {

class ShapeDrawable;

class OSGQTQML_EXPORT ShapeDrawableQtQml : public DrawableQtQml
{
  Q_OBJECT

public:
  class Index;

  ShapeDrawableQtQml(QObject *parent = 0);
  ShapeDrawableQtQml(Index *, QObject *parent = 0);

  void classBegin();

  ShapeDrawable* shapeDrawable();

  static ShapeDrawableQtQml* fromShapeDrawable(ShapeDrawable *drawable, QObject *parent = 0);
};

}

#endif // _OSG_SHAPEDRAWABLE_QTQML_
