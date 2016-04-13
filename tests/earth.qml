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
        ComboBox {
            model: [
                "GDAL", "Lines", "Polygons", "Labels",
                "OpenStreetMap", "ReadyMap", "VerticalScale"
            ]
            onActivated: {
                switch (index) {
                case 0: loader.source = "gdal_tiff.earth"
                    break;
                case 1: loader.source = "feature_draped_lines.earth"
                    break;
                case 2: loader.source = "feature_draped_polygons.earth"
                    break;
                case 3: loader.source = "feature_labels.earth"
                    break;
                case 4: loader.source = "openstreetmap.earth"
                    break;
                case 5: loader.source = "readymap-osm.earth"
                    break;
                case 6: loader.source = "vertical_scale.earth"
                    break;
                }
            }
        }
        Label {
            id: statusLabel
        }
        anchors {
            bottom: parent.bottom
        }
    }
}
