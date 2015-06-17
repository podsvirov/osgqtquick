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

    property int counter: 0

    Component {
        id: shapeFactory
        OSG.Box {
            property int level: 0
            center: Qt.vector3d(0, 0, -level)
            rotation: Qt.quaternion(Math.cos(level * aSlider.value / 2), 0, 0, -Math.sin(level * aSlider.value / 2))
            halfLengths: Qt.vector3d(0.5, 0.5, 0.1)
            Component.onCompleted: {
                level = counter
            }
        }
    }

    OSG.Box {
        id: box
        halfLengths: Qt.vector3d(0.5, 0.5, 0.1)
    }

    Component {
        id: transformFactory
        OSG.PositionAttitudeTransform {
            property int level: 0
            position: Qt.vector3d(0, 0, level)
            attitude: Qt.quaternion(Math.cos(level * aSlider.value / 2), 0, 0, Math.sin(level * aSlider.value / 2))
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(0, 1, 0, 0.5)
                    shape: box
                }
            }
            Component.onCompleted: {
                level = counter
            }
        }
    }

    OSG.Group {
        id: group

        OSG.Geode {
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 0.5)
                shape: OSG.CompositeShape {
                    id: composite

                    OSG.Box {
                        property int level: 1
                        center: Qt.vector3d(0, 0, -level)
                        rotation: Qt.quaternion(Math.cos(level * Math.PI / 90), 0, 0, Math.sin(level * Math.PI / 90))
                        halfLengths: Qt.vector3d(0.5, 0.5, 0.1)
                    }

                    OSG.Box {
                        property int level: 2
                        center: Qt.vector3d(0, 0, -level)
                        rotation: Qt.quaternion(Math.cos(level * Math.PI / 90), 0, 0, Math.sin(level * Math.PI / 90))
                        halfLengths: Qt.vector3d(0.5, 0.5, 0.1)
                    }
                }
            }
        }

        OSG.Geode {
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 1)
                shape: OSG.Sphere {
                    radius: 0.25
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

    RowLayout {
        Button {
            text: "Add"
            onClicked: {
                ++counter;
                group.addChild(transformFactory.createObject())
            }
        }
        Button {
            text: "Remove"
            onClicked: {
                if(counter > 0)
                {
                    --counter;
                    group.removeChild(counter + 2)
                }
            }
        }
        Slider { id: aSlider; minimumValue: 0; maximumValue: Math.PI / 8; value: 0; Layout.fillWidth: true }
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
