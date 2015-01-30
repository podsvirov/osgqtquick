#include "graphicscontext.hpp"
#include "graphicscontextindex.hpp"

#include <osg/GraphicsContext>

namespace osg {

GraphicsContextQtQml::Index::Index(GraphicsContext *graphicsContext) :
    ObjectQtQml::Index(graphicsContext),
    qthis(0)
{
    othis = graphicsContext;
}

void GraphicsContextQtQml::Index::classBegin()
{    
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

GraphicsContext *GraphicsContextQtQml::graphicsContext()
{
    return static_cast<Index*>(i)->othis;
}

GraphicsContextQtQml *GraphicsContextQtQml::fromGraphicsContext(GraphicsContext *GraphicsContext, QObject *parent)
{
    if(!GraphicsContext) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(GraphicsContext))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new GraphicsContextQtQml(new Index(GraphicsContext), parent);
}

}
