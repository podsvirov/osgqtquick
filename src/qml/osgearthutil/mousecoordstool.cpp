#include "mousecoordstool.hpp"
#include "mousecoordstoolindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthUtil/MouseCoordsTool>

namespace osgEarth {
namespace Util {

    MouseCoordsToolQtQml::Index::Index(MouseCoordsTool* tool)
        : osgGA::GUIEventHandlerQtQml::Index(tool)
    {
    }

    void MouseCoordsToolQtQml::Index::classBegin()
    {
    }

    void MouseCoordsToolQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            MouseCoordsTool* mct = new MouseCoordsTool(mapNode);
            callback = new MouseCoordsCallback(q(this));
            mct->addCallback(callback);
            setO(mct);
        }
        osgGA::GUIEventHandlerQtQml::Index::componentComplete();
    }

    MouseCoordsToolQtQml::MouseCoordsToolQtQml(QObject* parent)
        : osgGA::GUIEventHandlerQtQml(parent)
    {
    }

    MouseCoordsToolQtQml::MouseCoordsToolQtQml(MouseCoordsToolQtQml::Index* index, QObject* parent)
        : osgGA::GUIEventHandlerQtQml(index, parent)
    {
    }

    void MouseCoordsToolQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);
        i(this)->setQ(this);
        osgGA::GUIEventHandlerQtQml::classBegin();
    }

    MouseCoordsTool* MouseCoordsToolQtQml::mouseCoordsTool()
    {
        return o(this);
    }

    MouseCoordsToolQtQml* MouseCoordsToolQtQml::fromMouseCoordsTool(MouseCoordsTool* tool, QObject* parent)
    {
        if (!tool)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(tool)) {
            return static_cast<MouseCoordsToolQtQml*>(index->qtObject());
        }

        return new MouseCoordsToolQtQml(new Index(tool), parent);
    }

    osgEarth::MapNodeQtQml* MouseCoordsToolQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    QGeoCoordinate MouseCoordsToolQtQml::position() const
    {
        return i(this)->position;
    }

    void MouseCoordsToolQtQml::setPosition(const QGeoCoordinate& coord)
    {
        i(this)->position = coord;
    }

    void MouseCoordsToolQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        emit mapNodeChanged(mapNode);
    }

    MouseCoordsCallback::MouseCoordsCallback(MouseCoordsToolQtQml* mct)
    {
        m_mct = mct;
    }

    void MouseCoordsCallback::set(const GeoPoint& position, osg::View* view, MapNode* mapNode)
    {
        m_mct->setPosition(osgQt::qGeoPoint(position));
        emit m_mct->positionChanged(osgQt::qGeoPoint(position));
    }

    void MouseCoordsCallback::reset(osg::View* view, MapNode* mapNode)
    {
    }
}
}
