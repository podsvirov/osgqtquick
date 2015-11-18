// Qt
import QtQuick   2.0

// OpenSceneGraph
import osg       2.0 as OSG
import osgGA     2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

// Root item - 3D scene view
OSGViewer.View {
    width: 640; height: 480
    focus: true
    cameraManipulator: OSGGA.TrackballManipulator {}
    sceneData: OSG.Group {
        OSG.Geode {
            OSG.ShapeDrawable {
                color: "yellow"
                shape: OSG.Box {
                    halfLengths: Qt.vector3d(3, 2, 1)
                }
            }
        }
        OSG.MatrixTransform {
            matrix: Qt.matrix4x4(1, 0, 0, 6, 0, 1, 0, 4, 0, 0, 1, 2, 0, 0, 0, 1)
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: "green"
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(3, 2, 1)
                    }
                }
            }
            Component.onCompleted: console.log("matrix: " + matrix)
        }
    }
    Component.onCompleted: cameraManipulator.home()
}
