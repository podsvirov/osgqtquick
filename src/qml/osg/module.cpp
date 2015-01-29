#include "module.hpp"

#include "nodeindex.hpp"
#include "groupindex.hpp"

#include <osg/Group>

#include <osgQtQml/Object>

#include <osgQtQuick/Version>
#include <QtQml>

#include <QDebug>

namespace osg {

void regisgerQtQmlTypes(const char *uri)
{
    qmlRegisterType<osg::NodeQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Node");

    qmlRegisterType<osg::GroupQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Group");

    osgQtQml::Index::insertMake(&qtMakeIndex);
    osgQtQml::Index::insertMake(&osgMakeIndex);
}

osgQtQml::Index *qtMakeIndex(QObject *o)
{
    if(osgQtQml::Object *qtObj = qobject_cast<osgQtQml::Object*>(o))
    {
        return qtObj->index();
    }

    return 0;
}

osgQtQml::Index *osgMakeIndex(osg::Object *o)
{
    if(osg::Node *node = dynamic_cast<osg::Node*>(o))
    {
        if(osg::Group *group = node->asGroup())
        {
            return (new osg::GroupQtQml(new osg::GroupQtQml::Index(group)))->index();
        }

        return (new osg::NodeQtQml(new osg::NodeQtQml::Index(node)))->index();
    }

    return 0;
}

}
