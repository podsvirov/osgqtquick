
#include "modelnode.hpp"
#include "modelnodeindex.hpp"
#include <osg/Depth>
#include <osgEarth/GeoMath>
#include <osgEarth/Utils>
#include <osgEarthAnnotation/AnnotationNode>
#include <osgEarthAnnotation/AnnotationUtils>
#include <osgEarthAnnotation/BboxDrawable>
#include <osgEarthAnnotation/ModelNode>
#include <osgEarthSymbology/BBoxSymbol>
#include <osgEarthSymbology/ModelSymbol>
#include <osgEarthSymbology/Style>

namespace osgEarth {
namespace Annotation {

    ModelNodeQtQml::Index::Index(ModelNode* m)
        : GeoPositionNodeQtQml::Index(m)
    {
    }

    void ModelNodeQtQml::Index::classBegin()
    {
        //        //        if (!o(this))
        //        //            setO(new ModelNode(mapNode));
        //                GeoPositionNodeQtQml::Index::classBegin();
    }

    void ModelNodeQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->url()->setLiteral(url.toStdString());
            style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->autoScale() = true;
            ModelNode* modelNode = new ModelNode(this->mapNode, style);
            setO(modelNode);
            //            o(this)->setUserData(this);
        }
        GeoPositionNodeQtQml::Index::componentComplete();
    }

    ModelNodeQtQml::ModelNodeQtQml(QObject* parent)
        : GeoPositionNodeQtQml(parent)
    {
    }

    ModelNodeQtQml::ModelNodeQtQml(ModelNodeQtQml::Index* index, QObject* parent)
        : GeoPositionNodeQtQml(index, parent)
    {
    }

    void ModelNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        GeoPositionNodeQtQml::classBegin();
    }

    void ModelNodeQtQml::componentComplete()
    {
        GeoPositionNodeQtQml::componentComplete();
        //        o(this)->setUserData(this);
    }

    QString ModelNodeQtQml::url() const
    {
        return i(this)->url;
    }

    ModelNode* ModelNodeQtQml::modelNode()
    {
        return o(this);
    }

    ModelNodeQtQml* ModelNodeQtQml::fromModelNode(ModelNode* node, QObject* parent)
    {
        if (!node)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(node)) {
            return static_cast<ModelNodeQtQml*>(index->qtObject());
        }

        return new ModelNodeQtQml(new Index(node), parent);
    }

    void ModelNodeQtQml::setUrl(QString url)
    {
        if (!isComplete()) {
            i(this)->url = url;
            return;
        }

        //        osgEarth::Symbology::Style& style = o(this)->getStyle();
        //        auto symbol = style.getSymbol<osgEarth::Symbology::ModelSymbol>();

        //        if (symbol.url() == url)
        //            return;
        i(this)->url = url;

        emit urlChanged(url);
    }

    void ModelNodeQtQml::setLabel(QString label)
    {
        if (!isComplete()) {
            i(this)->label = label;
            return;
        }

        i(this)->label = label;

        emit labelChanged(label);
    }

    QString ModelNodeQtQml::label() const
    {
        return i(this)->label;
    }
}
} // namespace osgEarth::Annotation
