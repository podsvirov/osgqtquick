import QtQuick 2.0

import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgText 2.0 as OSGText
import osgViewer 2.0 as OSGViewer

OSGViewer.View {

    width: 640; height: 480

    cameraManipulator: OSGGA.TrackballManipulator {}

    sceneData: OSG.Geode {
        OSGText.Text3D {
            text: "Hello from osgQtQuick!"
            color: "yellow"
        }
    }
}
