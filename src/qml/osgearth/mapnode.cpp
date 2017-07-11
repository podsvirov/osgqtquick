#include "mapnode.hpp"
#include "mapnodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarth/TerrainEffect>
#include <osgEarth/TerrainEngineNode>

namespace osgEarth {

MapNodeQtQml::Index::Index(MapNode* mapNode)
    : GroupQtQml::Index(mapNode)
{
}

void MapNodeQtQml::Index::classBegin()
{
    //    if (!o(this))
    //        setO(new MapNode);

    //    GroupQtQml::Index::classBegin();
}

void MapNodeQtQml::Index::componentComplete()
{
    if (!o(this)) {
        setO(MapNode::findMapNode(graph));
    }
    GroupQtQml::Index::classBegin();
}

MapNodeQtQml::MapNodeQtQml(QObject* parent)
    : GroupQtQml(parent)
{
}

MapNodeQtQml::MapNodeQtQml(MapNodeQtQml::Index* index, QObject* parent)
    : GroupQtQml(index, parent)
{
}

void MapNodeQtQml::addEffect(TerrainEffectQtQml* effect)
{
    o(this)->getTerrainEngine()->addEffect(effect->terrainEffect());
}

void MapNodeQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    GroupQtQml::classBegin();
}

MapNode* MapNodeQtQml::mapNode()
{
    return o(this);
}

MapNodeQtQml* MapNodeQtQml::fromMapNode(MapNode* mapNode, QObject* parent)
{
    if (!mapNode)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(mapNode)) {
        return static_cast<MapNodeQtQml*>(index->qtObject());
    }

    return new MapNodeQtQml(new Index(mapNode), parent);
}

osg::NodeQtQml* MapNodeQtQml::graph() const
{
    return osg::NodeQtQml::fromNode(i(this)->graph);
}

void MapNodeQtQml::setGraph(osg::NodeQtQml* graph)
{
    if (!isComplete()) {
        i(this)->graph = graph->node();
        return;
    }
    i(this)->graph = graph->node();
}
}
