#include "annotationnode.hpp"
#include "annotationnodeindex.hpp"
#include "modelnode.hpp"
#include <osgEarthAnnotation/AnnotationNode>
#include <osgGA/GUIEventAdapter>
#include <osgQtQml/Index>

namespace osgEarth {
namespace Annotation {

    AnnotationNodeQtQml::Index::Index(AnnotationNode* node)
        : osg::GroupQtQml::Index(node)
    {
    }

    void AnnotationNodeQtQml::Index::classBegin()
    {
        //        if (!o(this))
        //            setO(new AnnotationNode);
        //        GroupQtQml::Index::classBegin();
    }

    AnnotationNodeQtQml::AnnotationNodeQtQml(QObject* parent)
        : osg::GroupQtQml(parent)
    {
    }

    AnnotationNodeQtQml::AnnotationNodeQtQml(AnnotationNodeQtQml::Index* index, QObject* parent)
        : osg::GroupQtQml(index, parent)
    {
    }

    void AnnotationNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);

        osg::GroupQtQml::classBegin();
    }

    AnnotationNode* AnnotationNodeQtQml::annotationNode()
    {
        return o(this);
    }

    AnnotationNodeQtQml* AnnotationNodeQtQml::fromAnnotationNode(AnnotationNode* node, QObject* parent)
    {
        if (!node)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(node)) {
            return static_cast<AnnotationNodeQtQml*>(index->qtObject());
        }
        AnnotationNodeQtQml* result = new AnnotationNodeQtQml(new Index(node), parent);
        result->classBegin();
        result->componentComplete();
        return result;
    }

    SimpleEventHandler::SimpleEventHandler(AnnotationGroupQtQml* group)
        : _group(group)
    {
    }

    void SimpleEventHandler::onClick(AnnotationNode* node, const EventArgs& details)
    {
        if (details.buttons == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
            //            AnnotationNodeQtQml* qNode = dynamic_cast<AnnotationNodeQtQml*>(node->getUserData());
            AnnotationNodeQtQml* qNode = AnnotationNodeQtQml::fromAnnotationNode(node);
            emit _group->click(qNode);
            emit qNode->click();
        }
    }

    AnnotationGroupQtQml::Index::Index(AnnotationGroup* group)
        : osg::GroupQtQml::Index(group)
    {
    }

    void AnnotationGroupQtQml::Index::classBegin()
    {
        if (!o(this))
            setO(new AnnotationGroup);

        GroupQtQml::Index::classBegin();
    }

    AnnotationGroupQtQml::AnnotationGroupQtQml(QObject* parent)
        : osg::GroupQtQml(parent)
    {
    }

    AnnotationGroupQtQml::AnnotationGroupQtQml(AnnotationGroupQtQml::Index* index, QObject* parent)
        : osg::GroupQtQml(index, parent)
    {
    }

    void AnnotationGroupQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        osg::GroupQtQml::classBegin();
    }

    void AnnotationGroupQtQml::componentComplete()
    {
        osg::GroupQtQml::componentComplete();
        osgEarth::Util::AnnotationEventCallback* cb = new osgEarth::Util::AnnotationEventCallback();
        cb->addHandler(new SimpleEventHandler(this));
        o(this)->addEventCallback(cb);
    }

    AnnotationGroup* AnnotationGroupQtQml::annotationGroup()
    {
        return o(this);
    }

    AnnotationGroupQtQml* AnnotationGroupQtQml::fromAnnotationNode(AnnotationGroup* node, QObject* parent)
    {
        if (!node)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(node)) {
            return static_cast<AnnotationGroupQtQml*>(index->qtObject());
        }

        return new AnnotationGroupQtQml(new Index(node), parent);
    }
}
}
