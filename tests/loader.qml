// Qt
import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

// OpenSceneGraph
import osg       2.0 as OSG
import osgDB     2.0 as OSGDB
import osgGA     2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

OSGViewer.View {
    width: 500; height: 500
    cameraManipulator: OSGGA.TrackballManipulator {}
    sceneData: OSGDB.Loader {
        source: "cow.osg"
        onNodeChanged: cameraManipulator.home()
    }
    focus: true
}
