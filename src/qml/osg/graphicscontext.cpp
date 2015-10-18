#include "graphicscontext.hpp"
#include "graphicscontextindex.hpp"

#include <osg/GraphicsContext>

namespace osg {

GraphicsContextQtQml::Index::Index(GraphicsContext *graphicsContext) :
    ObjectQtQml::Index(graphicsContext)
{
}

GraphicsContextQtQml::GraphicsContextQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

GraphicsContextQtQml::GraphicsContextQtQml(GraphicsContextQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void GraphicsContextQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ObjectQtQml::classBegin();
}

GraphicsContext *GraphicsContextQtQml::graphicsContext()
{
    return o(this);
}

GraphicsContextQtQml *GraphicsContextQtQml::fromGraphicsContext(GraphicsContext *graphicsContext, QObject *parent)
{
    if(!graphicsContext) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(graphicsContext))
    {
        return static_cast<GraphicsContextQtQml*>(index->qtObject());
    }

    GraphicsContextQtQml *result = new GraphicsContextQtQml(new Index(graphicsContext), parent);
    result->classBegin();

    return result;
}

}
