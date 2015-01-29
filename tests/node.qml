import QtQuick 2.0

import osg 2.0 as OSG

Rectangle {
    width: 100; height: 100

    OSG.Node {
        id: node
        Component.onCompleted: {
            console.log("OSG: " + node)
        }
    }

    OSG.Group {
        id: group
        Component.onCompleted: {
            console.log("addChild(node) = " + addChild(node))
            console.log("addChild(node) = " + addChild(node))
            console.log("removeChild(node) = " + removeChild(node))
            console.log("removeChild(node) = " + removeChild(node))
            console.log("OSG: " + group)
        }
    }

    Text {
        text: group.numChildren
        anchors.centerIn: parent
    }
}
