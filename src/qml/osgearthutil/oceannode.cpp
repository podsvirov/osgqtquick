#include "oceannode.hpp"
#include "oceannodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthUtil/Ocean>

namespace osgEarth {
namespace Util {

    OceanNodeQtQml::Index::Index(OceanNode* o)
        : osg::GroupQtQml::Index(o)
    {
    }
    void OceanNodeQtQml::Index::classBegin()
    {
    }

    void OceanNodeQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            OceanNode* ocean = OceanNode::create(mapNode);
            setO(ocean);
        }
    }

    OceanNodeQtQml::OceanNodeQtQml(QObject* parent)
        : osg::GroupQtQml(parent)
    {
    }

    OceanNodeQtQml::OceanNodeQtQml(OceanNodeQtQml::Index* index, QObject* parent)
        : osg::GroupQtQml(index, parent)
    {
    }

    void OceanNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        osg::GroupQtQml::classBegin();
    }

    osgEarth::MapNodeQtQml* OceanNodeQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    float OceanNodeQtQml::seaLevel() const
    {
        return i(this)->seaLevel;
    }

    float OceanNodeQtQml::alpha() const
    {
        return i(this)->alpha;
    }

    void OceanNodeQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        emit mapNodeChanged(mapNode);
    }

    void OceanNodeQtQml::setSeaLevel(float seaLevel)
    {
        if (!isComplete()) {
            i(this)->seaLevel = seaLevel;
            return;
        }
        i(this)->seaLevel = seaLevel;
        o(this)->setSeaLevel(seaLevel);
        emit seaLevelChanged(seaLevel);
    }

    void OceanNodeQtQml::setAlpha(float alpha)
    {
        if (!isComplete()) {
            i(this)->alpha = alpha;
            return;
        }

        i(this)->alpha = alpha;
        o(this)->setAlpha(alpha);
        emit alphaChanged(alpha);
    }
}
}
