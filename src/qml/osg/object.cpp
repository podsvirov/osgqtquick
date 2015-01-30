#include "object.hpp"
#include "objectindex.hpp"

#include <osg/Object>

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
