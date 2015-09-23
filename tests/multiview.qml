import QtQuick 2.0

import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

Rectangle {

    width: 640; height: 480

    color: "black"

    GridLayout {

        columns: 3

        rowSpacing: 2
        columnSpacing: 2

        anchors.fill: parent
        anchors.margins: 2

        NatureMorte {
            id: natureMorte
        }

        OSGViewer.View {
            Text {
                text: "NodeTrackerManipulator"
                color: "white"
                anchors.bottom: parent.bottom
            }
            cameraManipulator: OSGGA.NodeTrackerManipulator {
                trackNode: natureMorte
            }
            sceneData: natureMorte
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Slider {
            id: ballHeightSlider
            minimumValue: 0.2
            orientation: Qt.Vertical
            anchors.right: parent.right
            Layout.rowSpan: 2
            Layout.fillHeight: true
            onValueChanged: {
                natureMorte.ballTransform.position = Qt.vector3d(-0.2, 0.1, value)
            }
        }

        OSGViewer.View {
            Text {
                text: "OrbitManipulator"
                color: "white"
                anchors.bottom: parent.bottom
            }
            cameraManipulator: OSGGA.OrbitManipulator {}
            sceneData: natureMorte
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        OSGViewer.View {
            Text {
                text: "TrackballManipulator"
                color: "white"
                anchors.bottom: parent.bottom
            }
            cameraManipulator: OSGGA.TrackballManipulator {}
            sceneData: natureMorte
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
