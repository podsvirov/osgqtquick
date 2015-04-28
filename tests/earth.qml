// Qt
import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
// OpenSceneGraph
import osg 2.0 as OSG
import osgDB 2.0  as OSGDB
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer
// osgEarth
import osgEarthUtil 2.0 as OSGEarthUtil

Rectangle {
    width: 500; height: 500

    OSG.Notify {
        id: notifier
        onNotify: console.log(message);
    }

    OSGDB.Loader {
        id: loader
        //source: "openstreetmap.earth"
        source: "openstreetmap_flat.earth"
        onNodeChanged: {
            console.log("loader: " + getNode())
            view.cameraManipulator.home()
        }
    }

    OSGEarthUtil.EarthManipulator {
        id: manipulator
    }

    OSGViewer.View {
        id: view
        anchors.fill: parent
        sceneData: loader
        cameraManipulator: manipulator
    }

    ColumnLayout {
        Button {
            text: "Home"
            onClicked: manipulator.home()
        }
        Button {
            text: "Zoom"
            onClicked: manipulator.zoom(100, -0.1)
        }
        Button {
            text: "Rotate"
            onClicked: manipulator.rotate(Math.PI/ 4, Math.PI / 4)
        }
    }
}
