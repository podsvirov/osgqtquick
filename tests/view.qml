// Qt
import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
// OpenSceneGraph
import osg 2.0 as OSG
import osgDB 2.0  as OSGDB
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

Rectangle {
    width: 500; height: 500

    OSG.ShapeDrawable {
        id: sd
        color: Qt.rgba(1, 1, 1, 0.5)
        shape: OSG.Box {
            halfLengths: Qt.vector3d(0.5, 0.5, 0.05)
        }
        Component.onCompleted: {
            console.log("sd: " + sd)
            console.log("sd.shape: " + sd.shape)
        }
    }

    OSG.Geode {
        id: geode
        Component.onCompleted: {
            addDrawable(sd)
        }
    }

    OSGDB.Loader {
        id: loader
        source: "axes.osgt"
        onNodeChanged: {
            console.log("loader: " + getNode())
            view.cameraManipulator.home()
        }
    }

    OSG.PositionAttitudeTransform {
        id: transform
        position: Qt.vector3d(xSlider.value, ySlider.value, zSlider.value)
        Component.onCompleted: {
            addChild(geode)
            console.log("group: " + group)
        }
    }

    OSG.Group {
        id: group
        Component.onCompleted: {
            addChild(loader)
            addChild(transform)
            console.log("group: " + group)
        }
    }

    OSGViewer.View {
        id: view
        anchors.fill: parent
        sceneData: group
        cameraManipulator: OSGGA.TrackballManipulator {}
        //cameraManipulator: OSGGA.NodeTrackerManipulator {
        //    trackNode: geode
        //}
        //cameraManipulator: OSGGA.FlightManipulator {
        //    node: geode
        //}
    }

    Button {
        text: "Home"
        onClicked: view.cameraManipulator.home()
    }

    ColumnLayout {
        Slider { id: xSlider; minimumValue: -1; maximumValue: 1; Layout.fillWidth: true }
        Slider { id: ySlider; minimumValue: -1; maximumValue: 1; Layout.fillWidth: true }
        Slider { id: zSlider; minimumValue: -1; maximumValue: 1; Layout.fillWidth: true }
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
