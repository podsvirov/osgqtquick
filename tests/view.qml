// Qt
import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

// OpenSceneGraph
import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer

OSGViewer.View {
    width: 640; height: 480
    cameraManipulator: OSGGA.TrackballManipulator {}
    sceneData: OSG.Group {
        OSG.Geode {
            OSG.ShapeDrawable {
                color: Qt.rgba(1, 1, 0, 1)
                shape: OSG.Box {
                    halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
                }
            }
        }
    }
}
