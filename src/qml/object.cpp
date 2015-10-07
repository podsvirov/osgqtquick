#include "object.hpp"
#include "index.hpp"

#include <QDebug>

osgQtQml::Object::Object(QObject *parent) :
  QObject(parent), _i_ptr(0),
  _is_begin(false),
  _is_complete(false)
{
}

osgQtQml::Object::Object(osgQtQml::Index *i, QObject *parent) :
  QObject(parent), _i_ptr(i)
{
}

osgQtQml::Object::~Object()
{
    if(_i_ptr)
    {
        delete _i_ptr;
    }
}

void osgQtQml::Object::classBegin()
{
    if(_i_ptr)
    {
        _i_ptr->classBegin();
    }

    _is_begin = true;
}

void osgQtQml::Object::componentComplete()
{
    if(_i_ptr)
    {
        _i_ptr->componentComplete();
    }

    _is_complete = true;
}

osgQtQml::Index *osgQtQml::Object::index()
{
    return _i_ptr;
}
