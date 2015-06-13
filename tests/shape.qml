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

    OSG.Box {
        id: box
        halfLengths: Qt.vector3d(0.5, 0.5, 0.1)
    }

    OSG.ShapeDrawable {
        id: sdRed
        color: Qt.rgba(1, 0, 0, 0.5)
        shape: box
    }

    OSG.Geode {
        id: geodeRed
        Component.onCompleted: {
            addDrawable(sdRed)
        }
    }

    OSG.ShapeDrawable {
        id: sdYellow
        color: Qt.rgba(1, 1, 0, 0.5)
        shape: box
    }

    OSG.ShapeDrawable {
        id: sdGreen
        color: Qt.rgba(0, 1, 0, 0.5)
        shape: box
    }

    OSG.Geode {
        id: geodeGreen
        Component.onCompleted: {
            addDrawable(sdGreen)
        }
    }

    OSG.Group {
        id: group

        OSG.PositionAttitudeTransform {
            position: Qt.vector3d(xSlider.value, ySlider.value, zSlider.value)
            Component.onCompleted: {
                addChild(geodeGreen)
            }
        }

        OSG.Geode {
            id: geodeYellow
            Component.onCompleted: {
                addDrawable(sdYellow)
            }
        }

        OSG.PositionAttitudeTransform {
            position: Qt.vector3d(-xSlider.value, -ySlider.value, -zSlider.value)
            Component.onCompleted: {
                addChild(geodeRed)
            }
        }
    }

    OSGViewer.View {
        id: view
        anchors.fill: parent
        sceneData: group
        cameraManipulator: OSGGA.TrackballManipulator {}
    }

    Button {
        text: "Home"
        onClicked: {
            view.cameraManipulator.home()
        }
    }

    ColumnLayout {
        Slider { id: xSlider; minimumValue: -1; maximumValue: 1; value: 0.3; Layout.fillWidth: true }
        Slider { id: ySlider; minimumValue: -1; maximumValue: 1; value: 0.2; Layout.fillWidth: true }
        Slider { id: zSlider; minimumValue: -1; maximumValue: 1; value: 0.1; Layout.fillWidth: true }
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
