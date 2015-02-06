#include "object.hpp"
#include "index.hpp"

#include <osgQtQml/Index>

#include <QDebug>

namespace osgQtQuick {

Object::Object(QQuickItem *parent) :
  QQuickItem(parent), i(0)
{

}

Object::Object(Index *i, QQuickItem *parent) :
  QQuickItem(parent), i(i)
{
}

Object::~Object()
{
    if(i)
    {
        delete i;
    }
}

void Object::classBegin()
{
    if(i)
    {
        i->classBegin();
    }
    QQuickItem::classBegin();
}

void Object::componentComplete()
{
    if(i)
    {
        i->componentComplete();
    }
    QQuickItem::componentComplete();
}

Index *Object::index()
{
    return i;
}

}
