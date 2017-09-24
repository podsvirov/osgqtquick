#ifndef _OSGEARTH_ANNO_ANNOTATION_NODE_QTQML_
#define _OSGEARTH_ANNO_ANNOTATION_NODE_QTQML_ 1

#include <osg/GroupQtQml>
#include <osgEarthUtil/AnnotationEvents>

namespace osgEarth {
namespace Annotation {
    class AnnotationNode;
    // AnnotationNodeQtQml
    class OSGQTQML_EXPORT AnnotationNodeQtQml : public osg::GroupQtQml {
        Q_OBJECT

    public:
        class Index;
        AnnotationNodeQtQml(QObject* parent = 0);
        AnnotationNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        AnnotationNode* annotationNode();
        static AnnotationNodeQtQml* fromAnnotationNode(AnnotationNode* node, QObject* parent = 0);

    signals:
        void click();
    };

    class AnnotationGroupQtQml;

    // SimpleEventHandler
    class SimpleEventHandler : public osgEarth::Util::AnnotationEventHandler {
    public:
        SimpleEventHandler(AnnotationGroupQtQml* group);
        void onClick(AnnotationNode* node, const EventArgs& details);

    private:
        AnnotationGroupQtQml* _group;
    };

    // AnnotationGroup
    class AnnotationGroup : public osg::Group {
    public:
        AnnotationGroup() {}
    };

    // AnnotationGroupQtQml
    class OSGQTQML_EXPORT AnnotationGroupQtQml : public osg::GroupQtQml {
        Q_OBJECT
    public:
        friend SimpleEventHandler;
        class Index;
        AnnotationGroupQtQml(QObject* parent = 0);
        AnnotationGroupQtQml(Index* index, QObject* parent = 0);

        void classBegin();
        void componentComplete();

        AnnotationGroup* annotationGroup();
        static AnnotationGroupQtQml* fromAnnotationNode(AnnotationGroup* node, QObject* parent = 0);
    signals:
        void click(AnnotationNodeQtQml* node);
    };
}
}

#endif
