#ifndef _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_
#define _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_ 1

#include <osg/NodeQtQml>
#include <osgGA/CameraManipulatorQtQml>

namespace osgEarth {
namespace Util {

    class EarthManipulator;

    class OSGQTQML_EXPORT EarthManipulatorQtQml : public osgGA::CameraManipulatorQtQml {
        Q_OBJECT

        Q_ENUMS(TetherMode)
    public:
        class Index;
        enum TetherMode {
            TETHER_CENTER, // The camera will follow the center of the node.
            TETHER_CENTER_AND_ROTATION, // The camera will follow the node and all rotations made by the node
            TETHER_CENTER_AND_HEADING // The camera will follow the node and only follow heading rotation
        };

        EarthManipulatorQtQml(QObject* parent = 0);
        EarthManipulatorQtQml(Index*, QObject* parent = 0);

        void classBegin();

        Q_INVOKABLE void pan(double dx, double dy);
        Q_INVOKABLE void rotate(double dx, double dy);
        Q_INVOKABLE void zoom(double dx, double dy);
        Q_INVOKABLE void setTetherNode(osg::NodeQtQml* node, double duration_s);
        Q_INVOKABLE void setTetherMode(TetherMode value);

        Q_INVOKABLE void setViewpoint(osg::NodeQtQml* node, double duration_s = 0.0);

        EarthManipulator* earthManipulator();

        static EarthManipulatorQtQml* fromEarthManipulator(EarthManipulator* earthManipulator, QObject* parent = 0);
    };
}
}

#endif // _OSGEARTHUTIL_EARTHMANIPULATOR_QTQML_
