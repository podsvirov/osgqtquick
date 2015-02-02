import QtQuick 2.0
import QtQuick.Controls 1.0
import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

Rectangle {
    width: 500; height: 500

    OSG.Node {
        id: node
        Component.onCompleted: {
            console.log("node: " + node)
        }
    }

    OSG.Group {
        id: group
        Component.onCompleted: {
            //addChild(node)
            console.log("group: " + group)
        }
    }

    OSGViewer.View {
        id: view
        anchors.fill: parent
        cameraManipulator: OSGGA.TrackballManipulator {}
        Component.onCompleted: {
            setSceneData(group)
            sceneData.addChild(node)
            console.log("view.cameraManipulator: " + view.cameraManipulator)
            console.log("view.sceneData: " + view.sceneData)
        }
    }

    OSGViewer.View {
        sceneData: node
        cameraManipulator: OSGGA.TrackballManipulator {}

        width: parent.width / 2
        height: parent.height / 2
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    Button {
        text: "Home"
        onClicked: view.cameraManipulator.home()
    }
}
