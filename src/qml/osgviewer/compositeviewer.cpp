#include "compositeviewer.hpp"
#include "compositeviewerindex.hpp"

#include <osgViewer/CompositeViewer>

namespace osgViewer {

CompositeViewerQtQml::Index::Index(CompositeViewer *compositeViewer) :
    osg::ObjectQtQml::Index(compositeViewer)
{
}

void CompositeViewerQtQml::Index::classBegin()
{
    if(!o(this)) setO(new CompositeViewer);

    osg::ObjectQtQml::Index::classBegin();
}

CompositeViewerQtQml::CompositeViewerQtQml(QObject *parent) :
  osg::ObjectQtQml(parent)
{
}

CompositeViewerQtQml::CompositeViewerQtQml(CompositeViewerQtQml::Index *index, QObject *parent) :
  osg::ObjectQtQml(index, parent)
{
}

void CompositeViewerQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

CompositeViewer *CompositeViewerQtQml::compositeViewer()
{
    return o(this);
}

CompositeViewerQtQml *CompositeViewerQtQml::fromCompositeViewer(CompositeViewer *compositeViewer, QObject *parent)
{
    if(!compositeViewer) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(compositeViewer))
    {
        return static_cast<CompositeViewerQtQml*>(index->qtObject());
    }

    CompositeViewerQtQml *result = new CompositeViewerQtQml(new Index(compositeViewer), parent);
    result->classBegin();
    return result;
}

}
