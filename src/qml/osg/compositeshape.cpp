#include "compositeshape.hpp"
#include "compositeshapeindex.hpp"

#include <osgQtQml/Index>

#include <osg/Shape>

#include <QDebug>

/*!
   \qmltype CompositeShape
   \inherits Shape
   \inqmlmodule osg
   \brief Composition of shapes
 */

namespace osg {

CompositeShapeQtQml::Index::Index(CompositeShape *CompositeShape) :
    ShapeQtQml::Index(CompositeShape),
    qthis(0),
    _completeInfo(0)
{
  othis = CompositeShape;
}

CompositeShapeQtQml::Index::~Index()
{
  if(_completeInfo) delete _completeInfo;
}

void CompositeShapeQtQml::Index::classBegin()
{
    if(!othis) othis = new CompositeShape();
    ShapeQtQml::Index::othis = othis;
    ShapeQtQml::Index::qthis = qthis;

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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    ShapeQtQml::classBegin();
}

void CompositeShapeQtQml::componentComplete()
{
  ShapeQtQml::componentComplete();

  if(Index::CompleteInfo *info = static_cast<Index*>(i)->_completeInfo)
    {
      for(QList<ShapeQtQml*>::iterator it = info->child.begin();
          it != info->child.end(); ++it)
        {
          addChild(*it);
        }
  }
}

ShapeQtQml *CompositeShapeQtQml::getShape() const
{
    return ShapeQtQml::fromShape(static_cast<Index*>(i)->othis->getShape());
}

void CompositeShapeQtQml::setShape(ShapeQtQml *shape)
{
    osg::Shape *a = shape->shape();

    if(static_cast<Index*>(i)->othis->getShape() == a) return;

    static_cast<Index*>(i)->othis->setShape(a);

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
      static_cast<Index*>(i)->info()->child.append(shape);
      return true;
  }
  else
  {
      static_cast<CompositeShapeQtQml::Index*>(i)->othis->addChild(shape->shape());
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
    unsigned int index = static_cast<CompositeShapeQtQml::Index*>(i)->othis->findChildNo(shape->shape());
    if (index != static_cast<CompositeShapeQtQml::Index*>(i)->othis->getNumChildren())
    {
        static_cast<CompositeShapeQtQml::Index*>(i)->othis->removeChild(index);
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
        static_cast<Index*>(i)->othis->removeChild(
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
    return static_cast<Index*>(i)->othis->getNumChildren();
}

ShapeQtQml *CompositeShapeQtQml::getChild(int i)
{
  return osg::ShapeQtQml::fromShape(static_cast<Index*>(this->i)->othis->getChild(
                                        static_cast<unsigned int>(i)));
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
    return static_cast<Index*>(i)->othis;
}

CompositeShapeQtQml *CompositeShapeQtQml::fromCompositeShape(CompositeShape *compositeShape, QObject *parent)
{
    if(!compositeShape) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(compositeShape))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new CompositeShapeQtQml(new Index(compositeShape), parent);
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
