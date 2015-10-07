#ifndef _OSG_COMPOSITEVIEWER_QTQML_INDEX_
#define _OSG_COMPOSITEVIEWER_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osgViewer/CompositeViewerQtQml>

namespace osgViewer {

class OSGQTQML_EXPORT CompositeViewerQtQml::Index : public osg::ObjectQtQml::Index
{
public:
    typedef CompositeViewer OType;
    typedef CompositeViewerQtQml QType;
    friend class CompositeViewerQtQml;

public:
    Index(CompositeViewer *CompositeViewer = 0);
    void classBegin();

protected:
    CompositeViewer *othis;
    CompositeViewerQtQml *qthis;
};

}

#endif // _OSG_COMPOSITEVIEWER_QTQML_INDEX_
