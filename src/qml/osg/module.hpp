#ifndef _OSG_MODULE_QTQML_
#define _OSG_MODULE_QTQML_ 1

#include <osgQtQml/Index>

namespace osg {

OSGQTQML_EXPORT void registerQtQmlTypes(const char *uri);

OSGQTQML_EXPORT osgQtQml::Index* qtMakeIndex(QObject *o);
OSGQTQML_EXPORT osgQtQml::Index* osgMakeIndex(osg::Object *o);

}

#endif // _OSG_MODULE_QTQML_
