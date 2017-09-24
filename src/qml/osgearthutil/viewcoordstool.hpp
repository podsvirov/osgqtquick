#ifndef _OSGEARTHUTIL_VIEW_COORDS_TOOL_QTQML_
#define _OSGEARTHUTIL_VIEW_COORDS_TOOL_QTQML_ 1

#include <QGeoCoordinate>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthUtil/EarthManipulatorQtQml>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventHandlerQtQml>

namespace osgEarth {
namespace Util {
    class ViewCoordsToolQtQml;
    class ViewCoordsTool : public osgGA::GUIEventHandler {
    public:
        ViewCoordsTool(ViewCoordsToolQtQml* vct);
        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

    private:
        ViewCoordsToolQtQml* _vct;
    };

    class OSGQTQML_EXPORT ViewCoordsToolQtQml : public osgGA::GUIEventHandlerQtQml {
        Q_OBJECT
        Q_PROPERTY(MapNodeQtQml* mapNode READ mapNode WRITE setMapNode)
        Q_PROPERTY(QGeoCoordinate viewCoord READ viewCoord NOTIFY viewCoordChanged)
        Q_PROPERTY(QGeoCoordinate mouseCoord READ mouseCoord NOTIFY mouseCoordChanged)
        Q_PROPERTY(double heading READ heading NOTIFY headingChanged)
        Q_PROPERTY(EarthManipulatorQtQml* manip READ manip WRITE setManip)
        Q_PROPERTY(QGeoCoordinate eye READ eye NOTIFY eyeChanged)

    public:
        class Index;
        ViewCoordsToolQtQml(QObject* parent = 0);
        ViewCoordsToolQtQml(Index* index, QObject* parent = 0);
        virtual void classBegin();

        ViewCoordsTool* viewCoordsTool();
        static ViewCoordsToolQtQml* fromViewCoordsTool(ViewCoordsTool* tool, QObject* parent = 0);
        QGeoCoordinate viewCoord();
        EarthManipulatorQtQml* manip();
        double heading();
        void setViewCoord(const QGeoCoordinate& coord);
        void setMouseCoord(const QGeoCoordinate& coord);
        void setEye(const QGeoCoordinate& eye);
        void setHeading(double heading);
        EarthManipulator* getManip();
        MapNodeQtQml* mapNode();
        MapNode* getMapNode();
        QGeoCoordinate mouseCoord();

        QGeoCoordinate eye() const;

    public slots:
        void setManip(EarthManipulatorQtQml* manip);
        void setMapNode(MapNodeQtQml* mapNode);

    signals:
        void viewCoordChanged(QGeoCoordinate viewCoord);
        void headingChanged(double heading);
        void mouseCoordChanged(QGeoCoordinate mouseCoord);
        void eyeChanged(QGeoCoordinate eye);
    };
}
}
#endif
