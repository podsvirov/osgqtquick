// Qt
import QtQuick 2.0

// OpenSceneGraph
import osg       2.0 as OSG
import osgGA     2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

Rectangle {
    id: root
    width: 640; height: 480
    color: "white"

    OSGViewer.View {
        id: view

        x: m.x + m.width
        y: m.y + m.height

        width: s.x - m.width
        height: s.y - s.height

        focus: true

        cameraManipulator: OSGGA.TrackballManipulator {}

        sceneData: OSG.Geode {
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 1)
                shape: OSG.Box {
                    halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
                }
            }
        }
    }

    Text {
        id: m
        text: "<MOVE>"
        color: "green"
        x: 100; y: 50
        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }

        Text {
            id: s
            text: "<SIZE>"
            color: "green"
            x: 320; y: 240
            MouseArea {
                anchors.fill: parent
                drag.target: parent
            }
        }
    }
}
