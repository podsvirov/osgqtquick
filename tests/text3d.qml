import QtQuick 2.0

import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgText 2.0 as OSGText
import osgViewer 2.0 as OSGViewer

OSGViewer.View {

    id: view

    width: 640; height: 480

    cameraManipulator: OSGGA.TrackballManipulator {}

    sceneData: OSG.Geode {
        OSGText.Text3D {
            id: text3d
            text: "Hello from\n  osgQtQuick!"
            characterSize: characterSizeSlider.value
            characterDepth: characterDepthSlider.value
            color: "yellow"
            axisAlignment: "XZ_PLANE"
            style: OSGText.Style {
                widthRatio: styleWidthRationSlider.value
            }
            function updateDrawMode() {
                var mode = 0.0
                if(drawModeTEXTChecker.checked)
                {
                    mode |= OSGText.TextBase.TEXT
                }
                if(drawModeBOUNDINGBOXChecker.checked)
                {
                    mode |= OSGText.TextBase.BOUNDINGBOX
                }
                if(drawModeFILLEDBOUNDINGBOXChecker.checked)
                {
                    mode |= OSGText.TextBase.FILLEDBOUNDINGBOX
                }
                if(drawModeALIGNMENTChecker.checked)
                {
                    mode |= OSGText.TextBase.ALIGNMENT
                }
                drawMode = mode
            }
        }
    }

    Button {
        text: "Home"
        onClicked: {
            view.cameraManipulator.home()
        }
    }

    GridLayout {
        columns: 2
        anchors.right: parent.right
        Label {
            text: "TEXT :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        CheckBox {
            id: drawModeTEXTChecker
            checked: true
            onCheckedChanged: text3d.updateDrawMode()
        }
        Label {
            text: "BOUNDINGBOX :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        CheckBox {
            id: drawModeBOUNDINGBOXChecker
            onCheckedChanged: text3d.updateDrawMode()
        }
        Label {
            text: "FILLEDBOUNDINGBOX :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        CheckBox {
            id: drawModeFILLEDBOUNDINGBOXChecker
            onCheckedChanged: text3d.updateDrawMode()
        }
        Label {
            text: "ALIGNMENT :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        CheckBox {
            id: drawModeALIGNMENTChecker
            onCheckedChanged: text3d.updateDrawMode()
        }
    }

    GridLayout {
        columns: 2
        Label {
            text: "characterSize :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        Slider {
            id: characterSizeSlider
            value: 0.5
            Layout.fillWidth: true
        }
        Label {
            text: "characterDepth :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        Slider {
            id: characterDepthSlider
            value: 0.5
            Layout.fillWidth: true
        }
        Label {
            text: "style.widthRatio :"
            color: "white"
            Layout.alignment: Qt.AlignRight
        }
        Slider {
            id: styleWidthRationSlider
            value: 1.0
            Layout.fillWidth: true
        }
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    Component.onCompleted: {
        cameraManipulator.home()
        text3d.updateDrawMode()
    }
}
