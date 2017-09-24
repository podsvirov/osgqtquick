#include "objectlocator.hpp"
#include "objectlocatorindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthUtil/ObjectLocator>

namespace osgEarth {
namespace Util {
    ObjectLocatorNodeQtQml::Index::Index(ObjectLocatorNode* o)
        : MatrixTransformQtQml::Index(o)
        , parent(0)
        , mapNode(0)
        , object(0)
    {
    }
    void ObjectLocatorNodeQtQml::Index::classBegin()
    {
        //        MatrixTransformQtQml::Index::classBegin();
    }

    void ObjectLocatorNodeQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            ObjectLocatorNode* locator = new osgEarth::Util::ObjectLocatorNode(mapNode->getMap());
            locator->getLocator()->setPosition(osg::Vec3d(position.longitude(), position.latitude(), position.altitude()));
            osg::Node* node = NULL;
            if (object)
                node = object->node();
            else
                node = osgDB::readNodeFile(url.toStdString());
            locator->addChild(node);
            setO(locator);
        }
        osg::MatrixTransformQtQml::Index::componentComplete();
    }

    ObjectLocatorNodeQtQml::ObjectLocatorNodeQtQml(QObject* parent)
        : MatrixTransformQtQml(parent)
    {
    }

    ObjectLocatorNodeQtQml::ObjectLocatorNodeQtQml(ObjectLocatorNodeQtQml::Index* index, QObject* parent)
        : MatrixTransformQtQml(index, parent)
    {
    }

    void ObjectLocatorNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        osg::MatrixTransformQtQml::classBegin();
    }

    osgEarth::MapNodeQtQml* ObjectLocatorNodeQtQml::mapNode()
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    QGeoCoordinate ObjectLocatorNodeQtQml::position() const
    {
        return i(this)->position;
    }

    osg::NodeQtQml* ObjectLocatorNodeQtQml::object() const
    {
        return i(this)->object;
    }

    QString ObjectLocatorNodeQtQml::url() const
    {
        return i(this)->url;
    }

    void ObjectLocatorNodeQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        emit mapNodeChanged(mapNode);
    }

    void ObjectLocatorNodeQtQml::setPosition(QGeoCoordinate position)
    {
        if (!isComplete()) {
            i(this)->position = position;
            return;
        }
        //        auto _position = o(this)->getLocator()->getPosition();
        //        if (QGeoCoordinate(_position.x(), _position.y(), _position.z()) == position)
        //            return;

        //        i(this)->position = position;
        auto _locator = o(this)->getLocator();
        _locator->setPosition(osgQt::vec3d(position));
        emit positionChanged(position);
    }

    void ObjectLocatorNodeQtQml::setObject(osg::NodeQtQml* object)
    {
        if (!isComplete()) {
            i(this)->object = object;
            return;
        }
        i(this)->object = object;
        emit objectChanged(object);
    }

    void ObjectLocatorNodeQtQml::setUrl(QString url)
    {
        if (!isComplete()) {
            i(this)->url = url;
            return;
        }
        i(this)->url = url;
        emit urlChanged(url);
    }
}
}
