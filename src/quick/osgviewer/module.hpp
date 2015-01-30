#ifndef _OSGVIEWER_MODULE_QTQUICK_
#define _OSGVIEWER_MODULE_QTQUICK_ 1

#include <osgQtQuick/Export>
#include <osgQtQml/Index>

namespace osgViewer {

OSGQTQUICK_EXPORT void regisgerQtQuickTypes(const char *uri);

OSGQTQUICK_EXPORT osgQtQml::Index* qtMakeQuickIndex(QObject *o);
OSGQTQUICK_EXPORT osgQtQml::Index* osgMakeQuickIndex(osg::Object *o);

}

#endif // _OSGVIEWER_MODULE_QTQUICK_
