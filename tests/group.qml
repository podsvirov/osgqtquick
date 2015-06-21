import QtQuick 2.0

import osg 2.0 as OSG

Rectangle {
    id: root

    width: 300; height: 100

    OSG.Node
    {
        id: node
        name: "Node from root"
    }

    OSG.Group {
        id: group

        children: OSG.Node {
            name: "Node for children list"

        }

        OSG.Node {
            name: "Node from group"
        }

        Component.onCompleted: {
            addChild(node)
        }
    }

    Column {
        Repeater {
            model: group.children.length
            delegate: Text {
                text: index + " : " + group.children[index].name
            }
        }

        anchors.fill: parent
    }
}
