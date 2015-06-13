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
            console.log("getChild(0) = " + getChild(0))
            console.log("getChild(1) = " + getChild(1))
            console.log("removeChild(node) = " + removeChild(node))
            //console.log("removeChild(node) = " + removeChild(node))
            console.log("OSG: " + group)
            console.log("OSG: " + OSG)
        }
    }

    Text {
        text: "num = " + group.children.length
        anchors.centerIn: parent
    }
}
