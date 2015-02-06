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
        delete i;
    }
}

void osgQtQml::Object::classBegin()
{
    if(i)
    {
        i->classBegin();
    }
}

void osgQtQml::Object::componentComplete()
{
    if(i)
    {
        i->componentComplete();
    }
}

osgQtQml::Index *osgQtQml::Object::index()
{
    return i;
}
