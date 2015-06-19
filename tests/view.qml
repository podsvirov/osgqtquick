// Qt
import QtQuick 2.0

// OpenSceneGraph
import osg       2.0 as OSG       // Core types
import osgGA     2.0 as OSGGA     // GUI Abstraction
import osgViewer 2.0 as OSGViewer // Viewer functionality

// Root item - 3D scene view
OSGViewer.View {

    // Default view size
    width: 640; height: 480

    // Set favorite camera manipulator
    cameraManipulator: OSGGA.TrackballManipulator {}

    // Set scene for rendering
    sceneData: OSG.Geode {
        OSG.ShapeDrawable {
            color: Qt.rgba(1, 1, 0, 1)
            shape: OSG.Box {
                halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
            }
        }
    }
}
