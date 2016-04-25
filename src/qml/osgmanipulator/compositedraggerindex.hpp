#ifndef _OSGMANIPULATOR_COMPOSITEDRAGGER_QTQML_INDEX_
#define _OSGMANIPULATOR_COMPOSITEDRAGGER_QTQML_INDEX_ 1

#include <osgManipulator/CompositeDraggerQtQml>

#include <osgManipulator/DraggerQtQmlIndex>

namespace osgManipulator {

class OSGQTQML_EXPORT CompositeDraggerQtQml::Index : public DraggerQtQml::Index
{
public:
    typedef CompositeDragger OType;
    typedef CompositeDraggerQtQml QType;
    friend class CompositeDraggerQtQml;

public:
    Index(CompositeDragger *dragger = 0);
    ~Index();

protected:
    struct CompleteInfo;
    CompleteInfo *_completeInfo;

    CompleteInfo* info();
};

struct CompositeDraggerQtQml::Index::CompleteInfo
{
  QList<DraggerQtQml*> dragger;
};

inline CompositeDraggerQtQml::Index::CompleteInfo *CompositeDraggerQtQml::Index::info()
{
  return _completeInfo ? _completeInfo : _completeInfo = new CompleteInfo;
}

}

#endif // _OSGMANIPULATOR_COMPOSITEDRAGGER_QTQML_INDEX_
