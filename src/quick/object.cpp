#include "object.hpp"

#include <osgQtQml/Index>

#include <QDebug>

namespace osgQtQuick {

Object::Object(QQuickItem *parent) :
  QQuickItem(parent), i(0)
{

}

Object::Object(osgQtQml::Index *i, QQuickItem *parent) :
  QQuickItem(parent), i(i)
{
}

Object::~Object()
{
    if(i)
    {
        qDebug() << "Component" << metaObject()->className() << "destroy; qt:" << (void*)this << "osg:" << i->o_ptr.get();
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
    qDebug() << "Component" << this << "begun";
}

void Object::componentComplete()
{
    // do nothing
    qDebug() << "Component" << this << "completed";
    QQuickItem::componentComplete();
}

osgQtQml::Index *Object::index()
{
    return i;
}

}
