#include "module.hpp"

#include "annotationnode.hpp"
#include "circlenode.hpp"
#include "ellipsenode.hpp"
#include "geopositionnode.hpp"
#include "imageoverlay.hpp"
#include "labelnode.hpp"
#include "linestring.hpp"
#include "modelnode.hpp"
#include "placenode.hpp"
#include "rectanglenode.hpp"
#include <QtQml>
#include <osgQtQuick/Version>

#include <QDebug>

namespace osgEarth {
namespace Annotation {

    void registerQtQmlTypes(const char* uri)
    {
        qmlRegisterType<PlaceNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "PlaceNode");

        qmlRegisterType<CircleNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "CircleNode");

        qmlRegisterType<ModelNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "ModelNode");

        qmlRegisterType<LabelNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "LabelNode");

        qmlRegisterType<ImageOverlayQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "ImageOverlay");

        qmlRegisterType<RectangleNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "RectangleNode");

        qmlRegisterType<EllipseNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "EllipseNode");

        qmlRegisterUncreatableType<AnnotationNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "AnnotationNode", "[osgQtQuick] AnnotationNode is Uncreatable");

        qmlRegisterType<AnnotationGroupQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "AnnotationGroup");

        qmlRegisterType<GeoPositionNodeQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "GeoPositionNode");
        qmlRegisterType<LineStringQtQml>(
            uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
            "LineString");
    }
}
}
