#include "module.hpp"

#include "viewindex.hpp"

#include <osgViewer/View>

#include <osgQtQuick/Object>

#include <osgQtQuick/Version>
#include <QtQml/QtQml>

#include <QtCore/QDebug>

namespace osgViewer {

void registerQtQuickTypes(const char *uri)
{
    qmlRegisterType<osgViewer::ViewQtQuick>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "View");

    osgQtQml::Index::insertMake(&qtMakeQuickIndex);
    osgQtQml::Index::insertMake(&osgMakeQuickIndex);
}

osgQtQml::Index *qtMakeQuickIndex(QObject *o)
{
    if(osgQtQuick::Object *qtObj = qobject_cast<osgQtQuick::Object*>(o))
    {
        return qtObj->index();
    }

    return 0;
}

osgQtQml::Index *osgMakeQuickIndex(osg::Object *o)
{
    if(osgViewer::View *view = dynamic_cast<osgViewer::View*>(o))
    {
        return (new osgViewer::ViewQtQuick(new osgViewer::ViewQtQuick::Index(view)))->index();
    }

    return 0;
}

}
