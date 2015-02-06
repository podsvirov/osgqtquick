#ifndef _OSG_SHAPE_QTQML_
#define _OSG_SHAPE_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osg {

class Shape;

class OSGQTQML_EXPORT ShapeQtQml : public osg::ObjectQtQml
{
  Q_OBJECT

public:
  class Index;

  ShapeQtQml(QObject *parent = 0);
  ShapeQtQml(Index *index, QObject *parent = 0);

  void classBegin();

  Shape* shape();

  static ShapeQtQml* fromShape(Shape *shape, QObject *parent = 0);
};

}

#endif // _OSG_SHAPE_QTQML_
