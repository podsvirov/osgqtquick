#ifndef _OSG_COMPOSITE_SHAPE_QTQML_
#define _OSG_COMPOSITE_SHAPE_QTQML_ 1

#include <osg/ShapeQtQml>

#include <QQmlListProperty>

namespace osg {

class CompositeShape;

class OSGQTQML_EXPORT CompositeShapeQtQml : public ShapeQtQml
{
  Q_OBJECT

  Q_PROPERTY(osg::ShapeQtQml* shape READ getShape WRITE setShape NOTIFY shapeChanged)
  Q_PROPERTY(int numChildren READ getNumChildren NOTIFY numChildrenChanged)
  Q_PROPERTY(QQmlListProperty<osg::ShapeQtQml> children READ children NOTIFY numChildrenChanged)

  Q_CLASSINFO("DefaultProperty", "children")

public:
  class Index;

  CompositeShapeQtQml(QObject *parent = 0);
  CompositeShapeQtQml(Index *, QObject *parent = 0);

  void classBegin();
  void componentComplete();

  Q_INVOKABLE ShapeQtQml *getShape();
  Q_INVOKABLE void setShape(ShapeQtQml *shape);

  Q_INVOKABLE bool addChild(ShapeQtQml *shape);
  Q_INVOKABLE bool removeChild(ShapeQtQml *shape);
  Q_INVOKABLE bool removeChild(int pos);
  Q_INVOKABLE int getNumChildren() const;
  Q_INVOKABLE osg::ShapeQtQml* getChild(int i);

  QQmlListProperty<ShapeQtQml> children();

  CompositeShape* compositeShape();

  static CompositeShapeQtQml* fromCompositeShape(CompositeShape *compositeShape, QObject *parent = 0);

signals:
  void shapeChanged(ShapeQtQml *shape) const;
  void numChildrenChanged(int num);

protected:
  static int childrenCount(QQmlListProperty<osg::ShapeQtQml> *list);
  static ShapeQtQml* childrenAt(QQmlListProperty<osg::ShapeQtQml> *list, int index);
  static void childrenAppend(QQmlListProperty<osg::ShapeQtQml> *list, osg::ShapeQtQml *shape);
  static void childrenClear(QQmlListProperty<osg::ShapeQtQml> *list);
};

}

#endif // _OSG_COMPOSITE_SHAPE_QTQML_
