import QtQuick 2.0

import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgText 2.0 as OSGText
import osgViewer 2.0 as OSGViewer

OSGViewer.View {

    width: 640; height: 480

    cameraManipulator: OSGGA.TrackballManipulator {}

    sceneData: OSG.Geode {
        OSGText.Text3D {
            id: text3d
            text: "Hello from osgQtQuick!"
            characterSize: slider.value
            color: "yellow"
        }
    }

    GridLayout {
        columns: 2
        Label {
            text: "characterSize:"
            color: "white"
        }
        Slider {
            id: slider
            value: 0.5
            anchors.bottom: parent.bottom
            Layout.fillWidth: true
        }
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
