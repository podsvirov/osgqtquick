#ifndef _OSG_GRAPHICSCONTEXT_QTQML_INDEX_
#define _OSG_GRAPHICSCONTEXT_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osg/GraphicsContextQtQml>

namespace osg {

class OSGQTQML_EXPORT GraphicsContextQtQml::Index : public ObjectQtQml::Index
{
    friend class GraphicsContextQtQml;

public:
    Index(GraphicsContext *graphicsContext = 0);
    void classBegin();

protected:
    GraphicsContext *othis;
    GraphicsContextQtQml *qthis;
};

}

#endif // _OSG_GRAPHICSCONTEXT_QTQML_INDEX_
