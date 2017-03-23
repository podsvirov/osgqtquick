#include "compositeshape.hpp"
#include "compositeshapeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QtCore/QDebug>

/*!
   \qmltype CompositeShape
   \inherits Shape
   \inqmlmodule osg
   \brief Composition of shapes
 */

namespace osg {

CompositeShapeQtQml::Index::Index(CompositeShape *compositeShape) :
    ShapeQtQml::Index(compositeShape),
    _completeInfo(0)
{
}

CompositeShapeQtQml::Index::~Index()
{
  if(_completeInfo) delete _completeInfo;
}

void CompositeShapeQtQml::Index::classBegin()
{
    if(!o(this)) setO(new CompositeShape);

    ShapeQtQml::Index::classBegin();
}

CompositeShapeQtQml::CompositeShapeQtQml(QObject *parent) :
  ShapeQtQml(parent)
{
}

CompositeShapeQtQml::CompositeShapeQtQml(CompositeShapeQtQml::Index *index, QObject *parent) :
  ShapeQtQml(index, parent)
{
}

void CompositeShapeQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ShapeQtQml::classBegin();
}

void CompositeShapeQtQml::componentComplete()
{
  ShapeQtQml::componentComplete();

  if(Index::CompleteInfo *info = i(this)->_completeInfo)
    {
      for(QList<ShapeQtQml*>::iterator it = info->child.begin();
          it != info->child.end(); ++it)
        {
          addChild(*it);
        }
  }
}

ShapeQtQml *CompositeShapeQtQml::getShape()
{
    return ShapeQtQml::fromShape(o(this)->getShape());
}

void CompositeShapeQtQml::setShape(ShapeQtQml *shape)
{
    osg::Shape *a = shape->shape();

    if(o(this)->getShape() == a) return;

    o(this)->setShape(a);

    emit shapeChanged(shape);
}

/*!
   \qmlmethod osg::CompositeShape::addChild(osg::Shape shape)

   Add \l {osg::Shape}{shape} to composition.
 */

bool CompositeShapeQtQml::addChild(ShapeQtQml *shape)
{
  if(!shape) return false;
  if (!isComplete())
  {
      i(this)->info()->child.append(shape);
      return true;
  }
  else
  {
      o(this)->addChild(shape->shape());
      emit numChildrenChanged(getNumChildren());
      return true;
  }

  return false;
}

/*!
   \qmlmethod osg::CompositeShape::removeChild(osg::Shape shape)

   Remove \l {osg::Shape}{shape} from composition.
 */

bool CompositeShapeQtQml::removeChild(ShapeQtQml *shape)
{
    unsigned int index = o(this)->findChildNo(shape->shape());
    if (index != o(this)->getNumChildren())
    {
        o(this)->removeChild(index);
        emit numChildrenChanged(getNumChildren());
        return true;
    }

    return false;
}

bool CompositeShapeQtQml::removeChild(int pos)
{
    if (pos < 0) return false;

    if(pos < getNumChildren())
    {
        o(this)->removeChild(
                static_cast<unsigned int>(pos));
        emit numChildrenChanged(getNumChildren());
        return true;
    }

    return false;
}

/*!
   \qmlproperty int osg::CompositeShape::numChildren

   Number of children \l {osg::Shape}{shapes}
 */

int CompositeShapeQtQml::getNumChildren() const
{
    return o(this)->getNumChildren();
}

ShapeQtQml *CompositeShapeQtQml::getChild(int i)
{
  return osg::ShapeQtQml::fromShape(
              o(this)->getChild(static_cast<unsigned int>(i)));
}

/*!
   \qmlproperty list<osg::Shape> osg::CompositeShape::children

   List of children \l {osg::Shape}{shapes}
 */

QQmlListProperty<ShapeQtQml> CompositeShapeQtQml::children()
{
  return QQmlListProperty<osg::ShapeQtQml>(this, (void*)0,
                                          CompositeShapeQtQml::childrenAppend,
                                          CompositeShapeQtQml::childrenCount,
                                          CompositeShapeQtQml::childrenAt,
                                          CompositeShapeQtQml::childrenClear);
}

CompositeShape *CompositeShapeQtQml::compositeShape()
{
    return o(this);
}

CompositeShapeQtQml *CompositeShapeQtQml::fromCompositeShape(CompositeShape *compositeShape, QObject *parent)
{
    if(!compositeShape) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(compositeShape))
    {
        return static_cast<CompositeShapeQtQml*>(index->qtObject());
    }

    CompositeShapeQtQml *result = new CompositeShapeQtQml(new Index(compositeShape), parent);
    result->classBegin();
    return result;
}

int CompositeShapeQtQml::childrenCount(QQmlListProperty<ShapeQtQml> *list)
{
  return static_cast<CompositeShapeQtQml*>(list->object)->getNumChildren();
}

ShapeQtQml* CompositeShapeQtQml::childrenAt(QQmlListProperty<ShapeQtQml> *list, int index)
{
  return static_cast<CompositeShapeQtQml*>(list->object)->getChild(index);
}

void CompositeShapeQtQml::childrenAppend(QQmlListProperty<ShapeQtQml> *list, ShapeQtQml *shape)
{
  static_cast<CompositeShapeQtQml*>(list->object)->addChild(shape);
}

void CompositeShapeQtQml::childrenClear(QQmlListProperty<ShapeQtQml> *list)
{
    while(childrenCount(list))
    {
        static_cast<CompositeShapeQtQml*>(list->object)->removeChild(0);
    }
}

}
