#ifndef _OSGEARTH_ANNO_ANNOTATION_NODE_QTQML_INDEX_
#define _OSGEARTH_ANNO_ANNOTATION_NODE_QTQML_INDEX_ 1

#include "annotationnode.hpp"
#include <osg/GroupQtQmlIndex>

namespace osgEarth {
namespace Annotation {
    // AnnotationNodeQtQml
    class OSGQTQML_EXPORT AnnotationNodeQtQml::Index : public osg::GroupQtQml::Index {
    public:
        typedef AnnotationNode OType;
        typedef AnnotationNodeQtQml QType;
        friend class AnnotationNodeQtQml;

    public:
        Index(AnnotationNode* o = 0);
        void classBegin();
    };
    // AnnotationGroupQtQml
    class OSGQTQML_EXPORT AnnotationGroupQtQml::Index : public osg::GroupQtQml::Index {
    public:
        typedef AnnotationGroup OType;
        typedef AnnotationGroupQtQml QType;
        friend class AnnotationGroupQtQml;

    public:
        Index(AnnotationGroup* o = 0);
        void classBegin();
    };
}
}

#endif
