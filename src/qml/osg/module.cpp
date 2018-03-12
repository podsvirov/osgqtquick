#include "module.hpp"

#include "objectindex.hpp"
#include "statesetindex.hpp"
#include "nodeindex.hpp"
#include "notifyindex.hpp"
#include "groupindex.hpp"
#include "transformindex.hpp"
#include "cameraindex.hpp"
#include "drawableindex.hpp"
#include "shapedrawableindex.hpp"
#include "graphicscontextindex.hpp"
#include "transformindex.hpp"
#include "matrixtransformindex.hpp"
#include "positionattitudetransformindex.hpp"
#include "shapeindex.hpp"
#include "compositeshapeindex.hpp"
#include "boxindex.hpp"
#include "sphereindex.hpp"
#include "cylinderindex.hpp"
#include "geodeindex.hpp"

#include <osg/Group>

#include <osgQtQml/Object>

#include <osgQtQuick/Version>
#include <QtQml/QtQml>

#include <QtCore/QDebug>

namespace osg {

void registerQtQmlTypes(const char *uri)
{
    qmlRegisterUncreatableType<ObjectQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Object", "[osgQtQuick] Object is Uncreatable");

    qmlRegisterType<StateSetQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "StateSet");

    qmlRegisterType<NodeQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Node");

    qmlRegisterType<NotifyQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Notify");

    qmlRegisterType<GeodeQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Geode");

    qmlRegisterType<GroupQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Group");

    qmlRegisterType<TransformQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Transform");

    qmlRegisterType<MatrixTransformQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "MatrixTransform");

    qmlRegisterType<PositionAttitudeTransformQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "PositionAttitudeTransform");

    qmlRegisterType<CameraQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Camera");

    qmlRegisterUncreatableType<DrawableQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Drawable", "[osgQtQuick] Drawable is Uncreatable");

    qmlRegisterType<ShapeDrawableQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "ShapeDrawable");

    qmlRegisterUncreatableType<GraphicsContextQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "GraphicsContext", "[osgQtQuick] GraphicsContext is Uncreatable");

    qmlRegisterUncreatableType<ShapeQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Shape", "[osgQtQuick] Shape is Uncreatable");

    qmlRegisterType<CompositeShapeQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "CompositeShape");

    qmlRegisterType<BoxQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Box");

    qmlRegisterType<SphereQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Sphere");

    qmlRegisterType<CylinderQtQml>(
                uri, osgQtQuick_VERSION_MAJOR, osgQtQuick_VERSION_MINOR,
                "Cylinder");

    osgQtQml::Index::insertMake(&qtMakeIndex);
    osgQtQml::Index::insertMake(&osgMakeIndex);
}

osgQtQml::Index *qtMakeIndex(QObject *o)
{
    if(osgQtQml::Object *qtObj = qobject_cast<osgQtQml::Object*>(o))
    {
        return qtObj->index();
    }

    return 0;
}

osgQtQml::Index *osgMakeIndex(osg::Object *o)
{
    if(osg::Node *node = dynamic_cast<osg::Node*>(o))
    {
        if(osg::Group *group = node->asGroup())
        {
            return (new osg::GroupQtQml(new osg::GroupQtQml::Index(group)))->index();
        }

        return (new osg::NodeQtQml(new osg::NodeQtQml::Index(node)))->index();
    }

    return 0;
}

}
