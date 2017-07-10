// Qt
import QtQuick        2.0

import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

// OpenSceneGraph
import osg            2.0 as OSG
import osgGA          2.0 as OSGGA
import osgManipulator 2.0 as OSGManipulator
import osgViewer      2.0 as OSGViewer

// Root item - 3D scene view
OSGViewer.View {
    id: view
    width: 640; height: 480
    focus: true
    cameraManipulator: OSGGA.TrackballManipulator { id: manipulator}
    sceneData: OSG.Group {
        OSG.Geode {
            OSG.ShapeDrawable {
                color: "red"
                shape: OSG.Box {
                    halfLengths: Qt.vector3d(1, 1, 0.1)
                }
            }
        }
        OSG.MatrixTransform {
            id: transform
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(1, 1, 0, 1)
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(0.4, 0.4, 0.4)
                    }
                }
            }
        }
        OSGManipulator.TabPlaneDragger {
            id: dragger
            handleEvents: true
            Component.onCompleted: {
                addTransformUpdating(transform)
                setupDefaultGeometry()
            }
        }
    }

    Component.onCompleted: {
        cameraManipulator.home()
    }
}