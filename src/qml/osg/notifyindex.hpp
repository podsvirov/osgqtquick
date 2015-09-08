#ifndef _OSG_NOTIFY_QTQML_INDEX_
#define _OSG_NOTIFY_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/NotifyQtQml>

namespace osg {

class OSGQTQML_EXPORT NotifyQtQml::Index : public ObjectQtQml::Index
{
    friend class NotifyQtQml;

public:
    Index();
    void classBegin();

protected:
//    Notify *othis;
    NotifyQtQml *qthis;
};

}

#endif // _OSG_NOTIFY_QTQML_INDEX_
