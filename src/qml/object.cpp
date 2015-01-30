#include "object.hpp"
#include "index.hpp"

#include <QDebug>

osgQtQml::Object::Object(QObject *parent) :
  QObject(parent), i(0)
{
}

osgQtQml::Object::Object(osgQtQml::Index *i, QObject *parent) :
  QObject(parent), i(i)
{
}

osgQtQml::Object::~Object()
{
    if(i)
    {
        qDebug() << "Component" << metaObject()->className() << "destroy; qt:" << (void*)this << "osg:" << i->o_ptr.get();
        delete i;
    }
}

void osgQtQml::Object::classBegin()
{
    if(i)
    {
        i->classBegin();
    }
    qDebug() << "Component" << metaObject()->className() << "begining";
}

void osgQtQml::Object::componentComplete()
{
    // do nothing
    qDebug() << "Component" << metaObject()->className() << "completed";
}

osgQtQml::Index *osgQtQml::Object::index()
{
    return i;
}
