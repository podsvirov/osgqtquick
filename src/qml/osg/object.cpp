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
    osgQtQml::Index(object)
{
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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

/*!
   \qmlproperty string osg::Object::name

   Name of object
 */

QString ObjectQtQml::getName() const
{
    return QString::fromStdString(o(this)->getName());
}

void ObjectQtQml::setName(const QString &name)
{
    if(getName() == name) return;

    o(this)->setName(name.toStdString());

    emit nameChanged(name);
}

osg::Object *ObjectQtQml::object()
{
    return o(this);
}

ObjectQtQml *ObjectQtQml::fromObject(osg::Object *object, QObject *parent)
{
    if(!object) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(object))
    {
        return static_cast<ObjectQtQml*>(index->qtObject());
    }

    return new ObjectQtQml(new Index(object), parent);
}

}
