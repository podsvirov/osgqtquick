#ifndef _OSG_GEODE_QTQML_INDEX_
#define _OSG_GEODE_QTQML_INDEX_ 1

#include <osg/GeodeQtQml>

#include <osg/NodeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT GeodeQtQml::Index : public NodeQtQml::Index
{
public:
    typedef Geode OType;
    typedef GeodeQtQml QType;
    friend class GeodeQtQml;

public:
    Index(Geode *o = 0);
    ~Index();

    void classBegin();

protected:
    struct CompleteInfo;
    CompleteInfo *_completeInfo;

    CompleteInfo* info();
};

struct GeodeQtQml::Index::CompleteInfo
{
  QList<DrawableQtQml*> drawables;
};

inline GeodeQtQml::Index::CompleteInfo *GeodeQtQml::Index::info()
{
  return _completeInfo ? _completeInfo : _completeInfo = new CompleteInfo;
}

}

#endif // _OSG_GEODE_QTQML_INDEX_
