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

    OSG.Group {
        id: group

        OSG.PositionAttitudeTransform {
            position: Qt.vector3d(xSlider.value, ySlider.value, zSlider.value)
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(0, 1, 0, 0.5)
                    shape: box
                }
            }
        }

        OSG.Geode {
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 0.5)
                shape: OSG.Box {
                    center: Qt.vector3d(0, 0, 0.2)
                    halfLengths: Qt.vector3d(0.2, 0.2, 0.05)
                    rotation: Qt.quaternion(Math.cos(Math.PI / 8), 0, 0, Math.sin(Math.PI / 8))
                }
            }
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 0.5)
                shape: box
            }
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 0.5)
                shape: OSG.Box {
                    center: Qt.vector3d(0, 0, -0.2)
                    halfLengths: Qt.vector3d(0.2, 0.2, 0.05)
                }
            }
        }

        OSG.PositionAttitudeTransform {
            position: Qt.vector3d(-xSlider.value, -ySlider.value, -zSlider.value)
            attitude: Qt.quaternion(Math.cos(Math.PI / 8), 0, 0, Math.sin(Math.PI / 8))
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(1, 0, 0, 0.5)
                    shape: box
                }
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
