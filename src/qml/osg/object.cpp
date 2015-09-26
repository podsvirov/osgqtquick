#include "object.hpp"
#include "objectindex.hpp"

#include <osg/Object>

/*!
   \qmltype Object
   \inqmlmodule osg
   \brief Base type
 */

namespace osg {

ObjectQtQml::Index::Index(osg::Object *object) :
    osgQtQml::Index(object),
    qthis(0)
{
    othis = object;
}

void ObjectQtQml::Index::classBegin()
{    
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

void ObjectQtQml::Index::componentComplete()
{
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::componentComplete();
}

ObjectQtQml::ObjectQtQml(QObject *parent) :
  Object(parent)
{
}

ObjectQtQml::ObjectQtQml(ObjectQtQml::Index *index, QObject *parent) :
  Object(index, parent)
{
}

void ObjectQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

/*!
   \qmlproperty string osg::Object::name

   Name of object
 */

QString ObjectQtQml::getName() const
{
    return QString::fromStdString(static_cast<Index*>(i)->othis->getName());
}

void ObjectQtQml::setName(const QString &name)
{
    if(getName() == name) return;

    static_cast<Index*>(i)->othis->setName(name.toStdString());

    emit nameChanged(name);
}

osg::Object *ObjectQtQml::object()
{
    return static_cast<Index*>(i)->othis;
}

ObjectQtQml *ObjectQtQml::fromObject(osg::Object *object, QObject *parent)
{
    if(!object) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(object))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new ObjectQtQml(new Index(object), parent);
}

}
