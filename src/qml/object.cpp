#include "object.hpp"
#include "index.hpp"

#include <QDebug>

osgQtQml::Object::Object(QObject *parent) :
  QObject(parent), i(0),
  _isBegin(false),
  _isComplete(false)
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

    _isBegin = true;
}

void osgQtQml::Object::componentComplete()
{
    if(i)
    {
        i->componentComplete();
    }

    _isComplete = true;
}

osgQtQml::Index *osgQtQml::Object::index()
{
    return i;
}
