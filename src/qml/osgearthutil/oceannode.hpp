#ifndef _OSGEARTHUTIL_OCEAN_NODE_QTQML_
#define _OSGEARTHUTIL_OCEAN_NODE_QTQML_ 1

#include <osg/GroupQtQml>
#include <osgEarth/MapNodeQtQml>

namespace osgEarth {
namespace Util {
    class OceanNode;
    class OSGQTQML_EXPORT OceanNodeQtQml : public osg::GroupQtQml {
    public:
        Q_OBJECT
    public:
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(float seaLevel READ seaLevel WRITE setSeaLevel NOTIFY seaLevelChanged)
        Q_PROPERTY(float alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)

    public:
        class Index;
        OceanNodeQtQml(QObject* parent = 0);
        OceanNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        osgEarth::MapNodeQtQml* mapNode() const;
        float seaLevel() const;
        float alpha() const;

    public slots:
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);
        void setSeaLevel(float seaLevel);
        void setAlpha(float alpha);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
        void seaLevelChanged(float seaLevel);
        void alphaChanged(float alpha);

    private:
        osg::GroupQtQml* m_mapNode;
    };
} // Util
} // osgEarth

#endif
