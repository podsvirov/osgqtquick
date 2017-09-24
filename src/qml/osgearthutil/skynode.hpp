#ifndef _OSGEARTHUTIL_SKY_NODE_QTQML_
#define _OSGEARTHUTIL_SKY_NODE_QTQML_ 1

#include <osg/GroupQtQml>
#include <osg/ObjectQtQml>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthUtil/Sky>
#include <osgViewer/ModuleQtQuick>

namespace osgEarth {
namespace Util {
    class OSGQTQML_EXPORT SkyNodeQtQml : public osg::GroupQtQml {
    public:
        Q_OBJECT
    public:
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(bool sunVisible READ sunVisible WRITE setSunVisible NOTIFY sunVisibleChanged)
        Q_PROPERTY(bool moonVisible READ moonVisible WRITE setMoonVisible NOTIFY moonVisibleChanged)
        Q_PROPERTY(bool starsVisible READ starsVisible WRITE setStarsVisible NOTIFY starsVisibleChanged)
        Q_PROPERTY(bool atmosphereVisible READ atmosphereVisible WRITE setAtmosphereVisible NOTIFY atmosphereVisibleChanged)
        Q_PROPERTY(int lighting READ lighting WRITE setLighting NOTIFY lightingChanged)

    public:
        class Index;
        SkyNodeQtQml(QObject* parent = 0);
        SkyNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        osgEarth::MapNodeQtQml* mapNode() const;

        bool sunVisible() const;
        bool moonVisible() const;
        bool starsVisible() const;
        bool atmosphereVisible() const;
        int lighting() const;

    public slots:
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);
        void setSunVisible(bool sun);
        void setMoonVisible(bool moon);
        void setStarsVisible(bool stars);
        void setAtmosphereVisible(bool atmosphere);
        void setLighting(int lighting);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
        void sunVisibleChanged(bool sun);
        void moonVisibleChanged(bool moon);
        void starsVisibleChanged(bool stars);
        void atmosphereVisibleChanged(bool atmosphere);
        void lightingChanged(int lighting);
    };
}
}

#endif
