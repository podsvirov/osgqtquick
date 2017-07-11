#include "geodeticgraticule.hpp"
#include "geodeticgraticuleindex.hpp"

#include <osgEarth/MapNode>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/GraticuleNode>

namespace osgEarth {
namespace Util {

    GeodeticGraticuleQtQml::GeodeticGraticuleQtQml(QObject* parent)
        : osg::GroupQtQml(parent)
    {
    }

    GeodeticGraticuleQtQml::GeodeticGraticuleQtQml(GeodeticGraticuleQtQml::Index* index, QObject* parent)
        : osg::GroupQtQml(index, parent)
    {
    }

    void GeodeticGraticuleQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);
        i(this)->setQ(this);
        osg::GroupQtQml::classBegin();
    }

    GeodeticGraticuleQtQml::Index::Index(GraticuleNode* gr)
        : osg::GroupQtQml::Index(gr)
    {
    }

    void GeodeticGraticuleQtQml::Index::classBegin()
    {
    }

    void GeodeticGraticuleQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            GraticuleNode* gr = new GraticuleNode(mapNode);
            //            GeodeticGraticuleOptions opt = gr->getOptions();
            //            opt.lineStyle()->getOrCreate<LineSymbol>()->stroke()->color() = osgQt::swapColor(color);
            //            gr->setOptions(opt);
            gr->setVisible(visible);

            if (parent) { // bug?
                Controls::ControlCanvas* canvas = new Controls::ControlCanvas();
                parent->addChild(canvas);
                Controls::VBox* vbox = new Controls::VBox();
                canvas->addControl(vbox);
            }

            setO(gr);
        }
    }

    osgEarth::MapNodeQtQml* GeodeticGraticuleQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    osg::GroupQtQml* GeodeticGraticuleQtQml::parent() const
    {
        return osg::GroupQtQml::fromGroup(i(this)->parent);
    }

    QColor GeodeticGraticuleQtQml::color() const
    {
        return i(this)->color;
    }

    bool GeodeticGraticuleQtQml::visible() const
    {
        return o(this)->getVisible();
    }

    void GeodeticGraticuleQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
    }

    void GeodeticGraticuleQtQml::setParent(osg::GroupQtQml* parent)
    {
        if (!isComplete()) {
            i(this)->parent = parent->group();
            return;
        }

        i(this)->parent = parent->group();
    }

    void GeodeticGraticuleQtQml::setColor(QColor color)
    {
        if (!isComplete()) {
            i(this)->color = color;
            return;
        }

        i(this)->color = color;

        //        GeodeticGraticuleOptions opt = o(this)->getOptions();
        //        opt.lineStyle()->getOrCreate<LineSymbol>()->stroke()->color() = osgQt::swapColor(color);

        emit colorChanged(color);
    }

    void GeodeticGraticuleQtQml::setVisible(bool visible)
    {
        if (!isComplete()) {
            i(this)->visible = visible;
            return;
        }
        o(this)->setVisible(visible);

        emit visibleChanged(visible);
    }
}
}
