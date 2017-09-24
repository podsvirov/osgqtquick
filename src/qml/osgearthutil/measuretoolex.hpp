/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2016 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef OSGEARTHUTIL_MEASURETOOLEX_H
#define OSGEARTHUTIL_MEASURETOOLEX_H 1

#include <osg/Group>
#include <osgEarth/MapNode>
#include <osgEarth/MapNodeObserver>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthSymbology/Style>
#include <osgEarthUtil/Common>
#include <osgGA/GUIEventHandler>
#include <osgViewer/View>

namespace osgEarth {
namespace Util {
    using namespace osgEarth::Symbology;

    struct MeasureToolHandlerEx : public osgGA::GUIEventHandler, public MapNodeObserver {
    public:
        class MeasureToolEventHandler : public osg::Referenced {
        public:
            virtual void onDistanceChanged(MeasureToolHandlerEx* sender, double distance) {}
            virtual ~MeasureToolEventHandler() {}
        };

        typedef std::list<osg::ref_ptr<MeasureToolEventHandler> > MeasureToolEventHandlerList;

        MeasureToolHandlerEx(osg::Group* group, MapNode* mapNode);
        virtual ~MeasureToolHandlerEx();

        bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

        bool getLocationAt(osgViewer::View* view, double x, double y, double& lon, double& lat, double& alt);

        void clear();

        void addEventHandler(MeasureToolEventHandler* handler);

        void setMouseButton(int mouseButton);
        int getMouseButton() const;

        GeoInterpolation getGeoInterpolation() const;
        void setGeoInterpolation(GeoInterpolation geoInterpolation);

        void setIsPath(bool path);
        bool getIsPath() const;

        /** Sets the style of the measurment line (to something other than the default) */
        void setLineStyle(const Style& style);
        const Style& getLineStyle() const { return _feature->style().value(); }

        void setIntersectionMask(osg::Node::NodeMask intersectionMask) { _intersectionMask = intersectionMask; }
        osg::Node::NodeMask getIntersectionMask() const { return _intersectionMask; }

        osgEarth::Features::Feature* getFeature() const { return _feature.get(); }

        osg::Vec3 firstPos() { return _firstPos; }
        osg::Vec3 secondPos() { return _secondPos; }

    public: // MapNodeObserver
        virtual void setMapNode(MapNode* mapNode);
        virtual MapNode* getMapNode() { return _mapNode.get(); }

    protected:
        GeoInterpolation _geoInterpolation;
        void fireDistanceChanged();
        bool _lastPointTemporary;
        bool _gotFirstLocation;
        bool _finished;
        bool _mouseDown;
        float _mouseDownX, _mouseDownY;
        int _mouseButton;
        osg::ref_ptr<osg::Group> _group;

        osg::ref_ptr<osgEarth::Annotation::FeatureNode> _featureNode;
        osg::ref_ptr<osgEarth::Features::Feature> _feature;

        osg::ref_ptr<osgEarth::Annotation::FeatureNode> _extentFeatureNode;
        osg::ref_ptr<osgEarth::Features::Feature> _extentFeature;

        MeasureToolEventHandlerList _eventHandlers;
        bool _isPath;
        osg::observer_ptr<MapNode> _mapNode;
        osg::Node::NodeMask _intersectionMask;

        osg::Vec3 _firstPos;
        osg::Vec3 _secondPos;

        void rebuild();
    };
}
}
#endif
