import QtQuick 2.0

import osg 2.0 as OSG

Rectangle {
    width: 300; height: 100

    OSG.Node
    {
        id: node
    }

    OSG.Group {
        id: group

        child: OSG.Node {

        }

        OSG.Node {
        }

        Component.onCompleted: {
            addChild(node)
        }
    }

    Column {
        Repeater {
            model: group.child.length
            delegate: Text {
                text: index + " : " + group.child[index]
            }
        }

        anchors.fill: parent
    }
}
