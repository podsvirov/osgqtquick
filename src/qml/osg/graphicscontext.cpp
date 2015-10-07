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
    if(othis) setO(othis);
    if(qthis) setQ(qthis);

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
    if(!_i_ptr) _i_ptr = new Index();
    static_cast<Index*>(_i_ptr)->qthis = this;
    osgQtQml::Object::classBegin();
}

GraphicsContext *GraphicsContextQtQml::graphicsContext()
{
    return static_cast<Index*>(_i_ptr)->othis;
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
