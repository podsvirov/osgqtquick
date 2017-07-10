import QtQuick 2.0

import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

Rectangle {

    width: 640; height: 480

    color: "black"

    OSG.Geode {
        id: sceneData
        OSG.ShapeDrawable {
            color: Qt.rgba(1, 1, 0, 1)
            shape: OSG.Box {
                halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
            }
        }
    }

    GridLayout {

        columns: 2

        rowSpacing: 2
        columnSpacing: 2

        anchors.fill: parent
        anchors.margins: 2

        OSGViewer.View {
            id: leftView
            Text {
                text: "Default Camera"
                color: "white"
                anchors.bottom: parent.bottom
            }
            cameraManipulator: OSGGA.TrackballManipulator {}
            sceneData: sceneData
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        OSGViewer.View {
            id: rightView
            Text {
                text: "Custom Camera"
                color: "white"
                anchors.bottom: parent.bottom
            }
            camera: OSG.Camera {
                clearColor: Qt.rgba(0.2, 0.2, 0.4, 1.0)
                Component.onCompleted: {
                    getOrCreateStateSet().setGlobalDefaults()
                }
            }
            cameraManipulator: OSGGA.TrackballManipulator {}
            sceneData: sceneData
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    Text {
        text: "Both view should be identical"
        color: "white"
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
    }

    Component.onCompleted: {
        leftView.cameraManipulator.home()
        rightView.cameraManipulator.home()
    }
}
