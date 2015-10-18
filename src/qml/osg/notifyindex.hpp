#ifndef _OSG_NOTIFY_QTQML_INDEX_
#define _OSG_NOTIFY_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/NotifyQtQml>

namespace osg {

class OSGQTQML_EXPORT NotifyQtQml::Index : public osgQtQml::Index
{
public:
    typedef NotifyHandler OType;
    typedef NotifyQtQml QType;
    friend class NotifyQtQml;

public:
    Index(NotifyHandler *o = 0);
    void classBegin();
};

}

#endif // _OSG_NOTIFY_QTQML_INDEX_
