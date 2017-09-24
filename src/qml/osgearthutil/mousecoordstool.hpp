#ifndef OSGEARTHUTIL_MOUSE_COORDS_TOOL_QTQML_
#define OSGEARTHUTIL_MOUSE_COORDS_TOOL_QTQML_ 1
#include <QGeoCoordinate>
#include <osg/GroupQtQml>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthUtil/MouseCoordsTool>
#include <osgGA/GUIEventHandlerQtQml>

namespace osgEarth {
namespace Util {
    class MouseCoordsToolQtQml;
    class MouseCoordsCallback : public MouseCoordsTool::Callback {
    public:
        MouseCoordsCallback(MouseCoordsToolQtQml* mct);
        virtual ~MouseCoordsCallback() {}
        virtual void set(const GeoPoint& coords, osg::View* view, MapNode* mapNode);
        virtual void reset(osg::View* view, MapNode* mapNode);

    private:
        MouseCoordsToolQtQml* m_mct;
    };

    class MouseCoordsTool;
    class OSGQTQML_EXPORT MouseCoordsToolQtQml : public osgGA::GUIEventHandlerQtQml {
        Q_OBJECT
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(QGeoCoordinate position READ position NOTIFY positionChanged)

    public:
        class Index;
        MouseCoordsToolQtQml(QObject* parent = 0);
        MouseCoordsToolQtQml(Index*, QObject* parent = 0);

        virtual void classBegin();

        MouseCoordsTool* mouseCoordsTool();
        static MouseCoordsToolQtQml* fromMouseCoordsTool(MouseCoordsTool* manipulator, QObject* parent = 0);

        osgEarth::MapNodeQtQml* mapNode() const;
        QGeoCoordinate position() const;
        void setPosition(const QGeoCoordinate& coord);

    public slots:
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
        void positionChanged(QGeoCoordinate position);
    };
}
}

#endif
