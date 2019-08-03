import QtQml 2.0
import osg 2.0 as OSG

OSG.Group {

    property alias ballTransform: ballTransform

    OSG.Geode {

        OSG.ShapeDrawable {
            color: "red"
            shape: OSG.Box {
                halfLengths: Qt.vector3d(0.5, 0.5, 0.01)
                center: Qt.vector3d(0, 0, -0.01)
            }
        }
        OSG.ShapeDrawable {
            color: "green"
            shape: OSG.Box {
                halfLengths: Qt.vector3d(0.2, 0.1, 0.3)
                center: Qt.vector3d(0.2, 0.3, 0.3)
            }
        }

        OSG.ShapeDrawable {
            color: "blue"
            shape: OSG.Cylinder {
                center: Qt.vector3d(0.25, -0.05, 0.2)
                radius: 0.2
                height: 0.4
            }
        }

        OSG.ShapeDrawable {
            color: "magenta"
            shape: OSG.Cone {
                center: Qt.vector3d(-0.1, -0.2, 0.075)
                radius: 0.15
                height: 0.3
            }
        }
    }

    OSG.PositionAttitudeTransform {
        id: ballTransform
        position: Qt.vector3d(-0.2, 0.1, 0.2)
        OSG.Geode {
            OSG.ShapeDrawable {
                color: "yellow"
                shape: OSG.Sphere {
                    radius: 0.2

                }
            }
        }
    }
}
