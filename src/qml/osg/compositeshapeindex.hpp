#ifndef _OSG_COMPOSITE_SHAPE_QTQML_INDEX_
#define _OSG_COMPOSITE_SHAPE_QTQML_INDEX_ 1

#include <osg/CompositeShapeQtQml>

#include <osg/ShapeQtQmlIndex>

namespace osg {

class OSGQTQML_EXPORT CompositeShapeQtQml::Index : public ShapeQtQml::Index
{
    friend class CompositeShapeQtQml;

public:
    Index(CompositeShape *o = 0);
    ~Index();

    void classBegin();

protected:
    CompositeShape *othis;
    CompositeShapeQtQml *qthis;

    struct CompleteInfo;
    CompleteInfo *_completeInfo;

    CompleteInfo* info();
};

struct CompositeShapeQtQml::Index::CompleteInfo
{
  QList<ShapeQtQml*> child;
};

inline CompositeShapeQtQml::Index::CompleteInfo *CompositeShapeQtQml::Index::info()
{
  return _completeInfo ? _completeInfo : _completeInfo = new CompleteInfo;
}

}

#endif // _OSG_COMPOSITE_SHAPE_QTQML_INDEX_
