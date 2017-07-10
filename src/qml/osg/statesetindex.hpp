#ifndef _OSG_STATESET_QTQML_INDEX_
#define _OSG_STATESET_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/StateSetQtQml>

namespace osg {

class OSGQTQML_EXPORT StateSetQtQml::Index : public ObjectQtQml::Index
{
public:
    typedef StateSet OType;
    typedef StateSetQtQml QType;
    friend class StateSetQtQml;

public:
    Index(StateSet *o = 0);
    void classBegin();
};

}

#endif // _OSG_STATESET_QTQML_INDEX_
