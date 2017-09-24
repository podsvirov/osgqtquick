#ifndef _OSGEARTH_MAPNODE_QTQML_
#define _OSGEARTH_MAPNODE_QTQML_ 1

#include <osg/GroupQtQml>
#include <osgEarth/TerrainEffectQtQml>

namespace osgEarth {
class MapNode;
class OSGQTQML_EXPORT MapNodeQtQml : public osg::GroupQtQml {
    Q_OBJECT

    Q_PROPERTY(osg::NodeQtQml* graph READ graph WRITE setGraph)

public:
    class Index;

    MapNodeQtQml(QObject* parent = 0);
    MapNodeQtQml(Index* index, QObject* parent = 0);

    Q_INVOKABLE void addEffect(TerrainEffectQtQml* effect);

    void classBegin();

    MapNode* mapNode();

    static MapNodeQtQml* fromMapNode(MapNode* mapNode, QObject* parent = 0);
    osg::NodeQtQml* graph() const;

public slots:
    void setGraph(osg::NodeQtQml* graph);
};
}

#endif
