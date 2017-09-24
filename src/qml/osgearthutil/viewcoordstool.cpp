#include "viewcoordstool.hpp"
#include "viewcoordstoolindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarth/Terrain>
#include <osgEarth/TerrainEngineNode>
#include <osgEarth/Viewpoint>
#include <osgEarthUtil/EarthManipulator>
#include <osgViewer/Viewer>

namespace osgEarth {
namespace Util {

    ViewCoordsTool::ViewCoordsTool(ViewCoordsToolQtQml* vct)
        : _vct(vct)
    {
    }

    bool ViewCoordsTool::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
    {
        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
        if (ea.getEventType() == ea.FRAME) {
            osgEarth::Util::EarthManipulator* em = _vct->getManip();
            if (em) {
                osgEarth::Viewpoint vp = em->getViewpoint();
                GeoPoint pt = vp.focalPoint().get();
                double heading = vp.heading().get().as(Units::DEGREES);
                if (_vct) {
                    QGeoCoordinate viewCoord(pt.y(), pt.x(), vp.getRange());
                    _vct->setViewCoord(viewCoord);
                    _vct->setHeading(heading);
                }
            }

            MapNode* mapNode = 0;
            if (mapNode = _vct->getMapNode()) {

                osg::Vec3 eye, center, up;
                double lat, lon, alt;
                view->getCamera()->getViewMatrixAsLookAt(eye, center, up);
                mapNode->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(eye.x(), eye.y(), eye.z(), lat, lon, alt);

                _vct->setEye(QGeoCoordinate(lat, lon, alt));

                osg::Vec3d world;
                if (mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world)) {
                    GeoPoint map;
                    map.fromWorld(mapNode->getMapSRS(), world);
                    _vct->setMouseCoord(osgQt::qGeoPoint(map));
                }
            }
        }
        return false;
    }

    ViewCoordsToolQtQml::Index::Index(ViewCoordsTool* tool)
        : osgGA::GUIEventHandlerQtQml::Index(tool)
    {
    }

    void ViewCoordsToolQtQml::Index::classBegin()
    {
        if (!o(this))
            setO(new ViewCoordsTool(q(this)));

        osgGA::GUIEventHandlerQtQml::Index::classBegin();
    }

    ViewCoordsToolQtQml::ViewCoordsToolQtQml(QObject* parent)
        : osgGA::GUIEventHandlerQtQml(parent)
    {
    }

    ViewCoordsToolQtQml::ViewCoordsToolQtQml(ViewCoordsToolQtQml::Index* index, QObject* parent)
        : osgGA::GUIEventHandlerQtQml(index, parent)
    {
    }

    void ViewCoordsToolQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);
        i(this)->setQ(this);
        osgGA::GUIEventHandlerQtQml::classBegin();
    }

    ViewCoordsTool* ViewCoordsToolQtQml::viewCoordsTool()
    {
        return o(this);
    }

    ViewCoordsToolQtQml* ViewCoordsToolQtQml::fromViewCoordsTool(ViewCoordsTool* tool, QObject* parent)
    {
        if (!tool)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(tool)) {
            return static_cast<ViewCoordsToolQtQml*>(index->qtObject());
        }

        return new ViewCoordsToolQtQml(new Index(tool), parent);
    }

    QGeoCoordinate ViewCoordsToolQtQml::viewCoord()
    {
        return i(this)->viewCoord;
    }

    EarthManipulatorQtQml* ViewCoordsToolQtQml::manip()
    {
        return EarthManipulatorQtQml::fromEarthManipulator(i(this)->manip);
    }

    double ViewCoordsToolQtQml::heading()
    {
        return i(this)->heading;
    }

    void ViewCoordsToolQtQml::setViewCoord(const QGeoCoordinate& coord)
    {
        i(this)->viewCoord = coord;
        emit viewCoordChanged(coord);
    }

    void ViewCoordsToolQtQml::setMouseCoord(const QGeoCoordinate& coord)
    {
        i(this)->mouseCoord = coord;
        emit mouseCoordChanged(coord);
    }

    void ViewCoordsToolQtQml::setEye(const QGeoCoordinate& eye)
    {
        i(this)->eye = eye;
        emit eyeChanged(eye);
    }

    void ViewCoordsToolQtQml::setHeading(double heading)
    {
        i(this)->heading = heading;
        emit headingChanged(heading);
    }

    EarthManipulator* ViewCoordsToolQtQml::getManip()
    {
        return i(this)->manip;
    }

    MapNodeQtQml* ViewCoordsToolQtQml::mapNode()
    {
        return MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    MapNode* ViewCoordsToolQtQml::getMapNode()
    {
        return i(this)->mapNode;
    }

    QGeoCoordinate ViewCoordsToolQtQml::mouseCoord()
    {
        return i(this)->mouseCoord;
    }

    QGeoCoordinate ViewCoordsToolQtQml::eye() const
    {
        return i(this)->eye;
    }

    void ViewCoordsToolQtQml::setManip(EarthManipulatorQtQml* manip)
    {
        i(this)->manip = manip->earthManipulator();
    }

    void ViewCoordsToolQtQml::setMapNode(MapNodeQtQml* mapNode)
    {
        i(this)->mapNode = mapNode->mapNode();
    }
}
}
