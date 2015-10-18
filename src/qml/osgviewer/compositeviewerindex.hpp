#ifndef _OSG_COMPOSITEVIEWER_QTQML_INDEX_
#define _OSG_COMPOSITEVIEWER_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osgViewer/CompositeViewerQtQml>

#include <osgViewer/CompositeViewer>

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
    template<typename T>
    typename T::OType* o(T *p);

    void setO(CompositeViewer *o);

    CompositeViewer *o_ptr;
};

template<typename T>
inline typename T::OType* CompositeViewerQtQml::Index::o(T *p)
{
    return static_cast<typename T::OType*>(p->o_ptr);
}

inline void CompositeViewerQtQml::Index::setO(CompositeViewer *o)
{
    o_ptr = o;
    ObjectQtQml::Index::setO(o);
}

}

#endif // _OSG_COMPOSITEVIEWER_QTQML_INDEX_
