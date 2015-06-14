// Qt
import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

// OpenSceneGraph
import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

Rectangle {
    width: 500; height: 500

    property int levelIndex: 0
    property var player: null
    property var level: null
    property var cache: null
    property int numTargets: 0
    property int numBoxesOnTarget: 0

    /*
      Space floor / corridor
      .     target square
      $     box
      *     box on target square
      @     SokoMind pusher
      +     SokoMind pusher on target square
      #     wall
    */

    property var levels: [
        ['First',
         [
             '   #### ',
             '####  # ',
             '#  $. # ',
             '#     # ',
             '#@#$# # ',
             '#  .. ##',
             '###$   #',
             '  #    #',
             '  ######'
         ]
        ],
        ['Connection',
         [
             '   ####  ',
             '####  ## ',
             '#   $  # ',
             '#  *** # ',
             '#  . . ##',
             '## * *  #',
             ' ##***  #',
             '  # $ ###',
             '  # @ #  ',
             '  #####  '
         ]
        ],
        ['Two rooms',
         [
             ' ######### ',
             ' #   #   # ',
             ' # @ #   # ',
             '##$**$**$# ',
             '#  #. .# ##',
             '#  .*$*.  #',
             '#         #',
             '###########'
         ]
        ]
    ]

    function isCorridor(i, j)
    {
        return level[i][j] === ' '
    }

    function isTarget(i, j)
    {
        return level[i][j] === '.' || level[i][j] === '*' || level[i][j] === '+'
    }

    function isBox(i, j)
    {
        return level[i][j] === '$' || level[i][j] === '*'
    }

    function isPlayer(i, j)
    {
        return level[i][j] === '@' || level[i][j] === '+'
    }

    function isWall(i, j)
    {
        return level[i][j] === '#'
    }

    Component {
        id: corridorFactory
        OSG.PositionAttitudeTransform {
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(0.5, 0.5, 0.5)
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
                    }
                }
            }
        }
    }

    Component {
        id: targetFactory
        OSG.PositionAttitudeTransform {
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(1, 0, 0)
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(0.25, 0.75, 0.25)
                    }
                }
            }
        }
    }

    Component {
        id: boxFactory
        OSG.PositionAttitudeTransform {
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(0, 1, 0)
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
                    }
                }
            }

            function move(key)
            {
                var doNotMove = false;
                var x = 0; var z = 0
                switch (key) {
                case Qt.Key_Left:
                    x = position.x - 1
                    z = position.z
                    break
                case Qt.Key_Right:
                    x = position.x + 1
                    z = position.z
                    break
                case Qt.Key_Up:
                    x = position.x
                    z = position.z + 1
                    break
                case Qt.Key_Down:
                    x = position.x
                    z = position.z - 1
                    break
                default:
                    doNotMove = true;
                    break
                }
                var i = level.length - z
                var j = x
                if(!doNotMove && !isWall(i,j) && cache[i][j] === null)
                {
                    cache[level.length - position.z][position.x] = null
                    if(isTarget(level.length - position.z, position.x)) --numBoxesOnTarget
                    position = Qt.vector3d(x, 0, z)
                    cache[i][j] = this
                    if(isTarget(i,j)) ++numBoxesOnTarget
                }
            }
        }
    }

    Component {
        id: wallFactory
        OSG.PositionAttitudeTransform {
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(1, 0.65, 0)
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(0.5, 0.2, 0.5)
                    }
                }
            }
        }
    }

    Component {
        id: playerFactory
        OSG.PositionAttitudeTransform {
            OSG.Geode {
                OSG.ShapeDrawable {
                    color: Qt.rgba(0, 0, 1)
                    shape: OSG.Box {
                        halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
                    }
                }
            }

            function move(key)
            {
                var doNotMove = false;
                var x = 0; var z = 0
                switch (key) {
                case Qt.Key_Left:
                    x = position.x - 1
                    z = position.z
                    break
                case Qt.Key_Right:
                    x = position.x + 1
                    z = position.z
                    break
                case Qt.Key_Up:
                    x = position.x
                    z = position.z + 1
                    break
                case Qt.Key_Down:
                    x = position.x
                    z = position.z - 1
                    break
                default:
                    doNotMove = true;
                    break
                }
                var i = level.length - z
                var j = x
                if(!doNotMove)
                {
                    if(cache[i][j] !== null)
                    {
                        cache[i][j].move(key)
                    }
                    if(!isWall(i,j) && cache[i][j] === null)
                    {
                        position = Qt.vector3d(x, 0, z)
                    }
                }
            }
        }
    }

    OSG.Group {
        id: group
        function restart() {
            children = []
            numTargets = 0
            numBoxesOnTarget = 0
            cache = []
            for(var i = 0; i < level.length; ++i)
            {
                cache[i] = []
                for(var j = 0; j < level[0].length; ++j)
                {
                    var item = null
                    var posc = level[i][j]
                    cache[i][j] = null
                    if(isBox(i,j))
                    {
                        item = boxFactory.createObject();
                        item.position = Qt.vector3d(j, 0, level.length - i)
                        if(isTarget(i,j)) ++numBoxesOnTarget
                        cache[i][j] = item
                        addChild(item)
                    }
                    if(isTarget(i,j))
                    {
                        item = targetFactory.createObject();
                        item.position = Qt.vector3d(j, 0, level.length - i)
                        ++numTargets
                        addChild(item)
                    }
                    if(isWall(i,j))
                    {
                        item = wallFactory.createObject();
                        item.position = Qt.vector3d(j, 0, level.length - i)
                        addChild(item)
                    }
                    if (isPlayer(i,j))
                    {
                        item = playerFactory.createObject();
                        item.position = Qt.vector3d(j, 0, level.length - i)
                        player = item
                        addChild(item)
                    }
                }
            }
        }
        Component.onCompleted: {
            level = levels[levelIndex][1]
            group.restart()
            view.cameraManipulator.home()
        }
    }

    function previousLevel()
    {
        if(levelIndex > 0)
        {
            --levelIndex
            level = levels[levelIndex][1]
            group.restart()
            view.cameraManipulator.home()
        }
    }

    function nextLevel()
    {
        if(levelIndex + 1 < levels.length)
        {
            ++levelIndex
            level = levels[levelIndex][1]
            group.restart()
            view.cameraManipulator.home()
        }
    }

    OSGViewer.View {
        id: view
        anchors.fill: parent
        sceneData: group
        cameraManipulator: OSGGA.TrackballManipulator {}
        Component.onCompleted: camera.clearColor = Qt.rgba(0.5, 0.5, 0.5)
    }

    Item {
        focus: true
        anchors.fill: parent
        Keys.onPressed: {
            player.move(event.key)
        }
    }

    Text {
        text: "Home"
        color: "white"
        font.pixelSize: 20
        MouseArea {
            anchors.fill: parent
            onClicked: {
                view.cameraManipulator.home()
            }
        }
    }
    Row {
        Text {
            text: "<<"
            color: "white"
            font.pixelSize: 20
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    previousLevel()
                }
            }
        }
        Text {
            text: levels[levelIndex][0]
            color: "white"
            font.pixelSize: 20
        }
        Text {
            text: ">>"
            color: "white"
            font.pixelSize: 20
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    nextLevel()
                }
            }
        }
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        text: "Targets: " + numBoxesOnTarget + "/" + numTargets
        color: "white"
        font.pixelSize: 20
        anchors.right: parent.right
    }
    Text {
        visible: numBoxesOnTarget === numTargets
        text: "You Win!"
        color: "white"
        font.pixelSize: 50
        anchors.centerIn: parent

    }
    Text {
        text: "Use arrow keys to navigate"
        color: "white"
        font.pixelSize: 20
        anchors.bottom: parent.bottom
    }
    Text {
        text: "Restart"
        color: "white"
        font.pixelSize: 20
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        MouseArea {
            anchors.fill: parent
            onClicked: {
                group.restart()
            }
        }
    }
}
