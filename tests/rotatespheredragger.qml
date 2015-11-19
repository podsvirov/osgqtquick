// Qt
import QtQuick        2.0

// OpenSceneGraph
import osg            2.0 as OSG
import osgGA          2.0 as OSGGA
import osgManipulator 2.0 as OSGManipulator
import osgViewer      2.0 as OSGViewer

// Root item - 3D scene view
OSGViewer.View {
    width: 640; height: 480
    focus: true
    cameraManipulator: OSGGA.TrackballManipulator {}
    sceneData: OSG.Group {
        OSGManipulator.RotateSphereDragger {
            draggerActive: true
            color: "lightgreen"
            pickColor: "lightblue"
            Component.onCompleted: setupDefaultGeometry()
        }
    }
    Component.onCompleted: cameraManipulator.home()
}
