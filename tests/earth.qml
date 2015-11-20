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
        notifyLevel: OSG.Notify.WARN
        onNotify: console.log(message);
    }

    OSGDB.Loader {
        id: loader
        source: "gdal_tiff.earth"
        onNodeChanged: {
            console.log("loader.node: " + getNode())
            view.cameraManipulator.home()
        }
        onStatusChanged: {
            switch(status)
            {
            case OSGDB.Loader.Null:
                statusLabel.text = "";
                break;
            case OSGDB.Loader.Loading:
                statusLabel.text = "Loading...";
                break;
            case OSGDB.Loader.Ready:
                statusLabel.text = "Ready";
                break;
            case OSGDB.Loader.Error:
                statusLabel.text = "Error";
                break;
            }
        }
    }

    OSGEarthUtil.EarthManipulator {
        id: manipulator
    }

    OSGViewer.View {
        id: view
        focus: true
        anchors.fill: parent
        camera.clearColor: "lightgray"
        sceneData: loader
        cameraManipulator: manipulator
        Keys.onPressed: {
            if(event.key === Qt.Key_Space) cameraManipulator.home()
        }
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

    RowLayout {
        Button {
            text: "GDAL"
            onClicked: loader.source = "gdal_tiff.earth"
        }
        Button {
            text: "OpenStreetMap"
            onClicked: loader.source = "openstreetmap.earth"
        }
        Button {
            text: "ReadyMap"
            onClicked: loader.source = "readymap-osm.earth"
        }
        Button {
            text: "VerticalScale"
            onClicked: loader.source = "vertical_scale.earth"
        }
        Label {
            id: statusLabel
        }
        anchors {
            bottom: parent.bottom
        }
    }
}
