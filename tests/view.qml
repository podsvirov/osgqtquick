import QtQuick 2.0
import osg 2.0 as OSG
import osgViewer 2.0 as OSGViewer

Rectangle {
    width: 100; height: 100

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
        Component.onCompleted: {
            setSceneData(group)
            sceneData.addChild(node)
            console.log("view: " + view)
            console.log("view.sceneData: " + view.sceneData)
        }
    }

    Text {
        //text: "" + view.sceneData//.numChildren
        text: group.numChildren
        anchors.centerIn: parent
    }
}
