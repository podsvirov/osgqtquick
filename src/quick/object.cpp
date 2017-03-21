#include "object.hpp"
#include "index.hpp"

#include <osgQtQml/Index>

#include <QtCore/QDebug>

namespace osgQtQuick {

Object::Object(QQuickItem *parent) :
  QQuickItem(parent), _i_ptr(0)
{

}

Object::Object(Index *i, QQuickItem *parent) :
  QQuickItem(parent), _i_ptr(i)
{
}

Object::~Object()
{
    if(_i_ptr)
    {
        delete _i_ptr;
    }
}

void Object::classBegin()
{
    if(_i_ptr)
    {
        _i_ptr->classBegin();
    }
    QQuickItem::classBegin();
}

void Object::componentComplete()
{
    if(_i_ptr)
    {
        _i_ptr->componentComplete();
    }
    QQuickItem::componentComplete();
}

Index *Object::index()
{
    return _i_ptr;
}

}
