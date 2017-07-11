#include "skynode.hpp"
#include "skynodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthUtil/Shadowing>

#include <osgViewer/View>

namespace osgEarth {
namespace Util {

    SkyNodeQtQml::Index::Index(SkyNode* o)
        : osg::GroupQtQml::Index(o)
        , sunVisible(true)
        , moonVisible(true)
        , starsVisible(true)
        , atmosphereVisible(true)
    {
    }

    void SkyNodeQtQml::Index::classBegin()
    {
    }

    void SkyNodeQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            osgEarth::Util::SkyNode* skyNode = osgEarth::Util::SkyNode::create(mapNode);
            skyNode->setSunVisible(sunVisible);
            skyNode->setMoonVisible(moonVisible);
            skyNode->setStarsVisible(starsVisible);
            skyNode->setAtmosphereVisible(atmosphereVisible);
            setO(skyNode);
        }
    }

    SkyNodeQtQml::SkyNodeQtQml(QObject* parent)
        : osg::GroupQtQml(parent)
    {
    }

    SkyNodeQtQml::SkyNodeQtQml(SkyNodeQtQml::Index* index, QObject* parent)
        : osg::GroupQtQml(index, parent)
    {
    }

    void SkyNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        osg::GroupQtQml::classBegin();
    }

    osgEarth::MapNodeQtQml* SkyNodeQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    bool SkyNodeQtQml::sunVisible() const
    {
        return o(this) ? o(this)->getSunVisible() : i(this)->sunVisible;
    }

    bool SkyNodeQtQml::moonVisible() const
    {
        return o(this) ? o(this)->getMoonVisible() : i(this)->moonVisible;
    }

    bool SkyNodeQtQml::starsVisible() const
    {
        return o(this) ? o(this)->getStarsVisible() : i(this)->starsVisible;
    }

    bool SkyNodeQtQml::atmosphereVisible() const
    {
        return o(this) ? o(this)->getAtmosphereVisible() : i(this)->atmosphereVisible;
    }

    int SkyNodeQtQml::lighting() const
    {
        return o(this) ? o(this)->getLighting() : i(this)->lighting;
    }

    void SkyNodeQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        emit mapNodeChanged(mapNode);
    }

    void SkyNodeQtQml::setSunVisible(bool visible)
    {
        if (!isComplete()) {
            i(this)->sunVisible = visible;
            return;
        }

        i(this)->sunVisible = visible;
        o(this)->setSunVisible(visible);
        emit sunVisibleChanged(visible);
    }

    void SkyNodeQtQml::setMoonVisible(bool visible)
    {
        if (!isComplete()) {
            i(this)->moonVisible = visible;
            return;
        }
        i(this)->moonVisible = visible;
        o(this)->setMoonVisible(visible);
        emit moonVisibleChanged(visible);
    }

    void SkyNodeQtQml::setStarsVisible(bool visible)
    {
        if (!isComplete()) {
            i(this)->starsVisible = visible;
            return;
        }
        i(this)->starsVisible = visible;
        o(this)->setStarsVisible(visible);
        emit starsVisibleChanged(visible);
    }

    void SkyNodeQtQml::setAtmosphereVisible(bool visible)
    {
        if (!isComplete()) {
            i(this)->atmosphereVisible = visible;
            return;
        }
        i(this)->atmosphereVisible = visible;
        o(this)->setAtmosphereVisible(visible);
        emit atmosphereVisibleChanged(visible);
    }

    void SkyNodeQtQml::setLighting(int lighting)
    {
        if (!isComplete()) {
            i(this)->lighting = lighting;
            return;
        }
        i(this)->lighting = lighting;
        o(this)->setLighting(lighting);
        emit lightingChanged(lighting);
    }
}
}
