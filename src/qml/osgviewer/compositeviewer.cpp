#include "compositeviewer.hpp"
#include "compositeviewerindex.hpp"

#include <osgViewer/CompositeViewer>

namespace osgViewer {

CompositeViewerQtQml::Index::Index(CompositeViewer *compositeViewer) :
    osg::ObjectQtQml::Index(compositeViewer),
    qthis(0)
{
    othis = compositeViewer;
}

void CompositeViewerQtQml::Index::classBegin()
{
    if(!othis) othis = new CompositeViewer();

    if(othis) setO(othis);
    if(qthis) setQ(qthis);

    osgQtQml::Index::classBegin();
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
    if(!_i_ptr) _i_ptr = new Index();
    static_cast<Index*>(_i_ptr)->qthis = this;
    osgQtQml::Object::classBegin();
}

CompositeViewer *CompositeViewerQtQml::compositeViewer()
{
    return static_cast<Index*>(_i_ptr)->othis;
}

CompositeViewerQtQml *CompositeViewerQtQml::fromCompositeViewer(CompositeViewer *compositeViewer, QObject *parent)
{
    if(!compositeViewer) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(compositeViewer))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new CompositeViewerQtQml(new Index(compositeViewer), parent);
}

}
