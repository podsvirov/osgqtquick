import QtQuick 2.0
import osg 2.0 as OSG
import osgViewer 2.0 as OSGViewer

Rectangle {
    width: 100; height: 100

    OSG.Node {
        id: node
    }

    OSGViewer.View {
        id: view
        anchors.fill: parent
        Component.onCompleted: {
            console.log("OSG: " + view)
        }
    }
}
