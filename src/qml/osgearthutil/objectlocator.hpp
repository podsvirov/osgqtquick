#ifndef _OSGEARTH_UTIL_OBJECT_LOCATOR_QTQML_
#define _OSGEARTH_UTIL_OBJECT_LOCATOR_QTQML_ 1

#include <QGeoCoordinate>
#include <osg/GroupQtQml>
#include <osg/MatrixTransformQtQml>
#include <osg/NodeQtQml>
#include <osgEarth/MapNodeQtQml>

namespace osgEarth {
namespace Util {
    class ObjectLocatorNode;
    class OSGQTQML_EXPORT ObjectLocatorNodeQtQml : public osg::MatrixTransformQtQml {
    public:
        Q_OBJECT
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
        Q_PROPERTY(osg::NodeQtQml* object READ object WRITE setObject NOTIFY objectChanged)
        Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

    public:
        class Index;

        ObjectLocatorNodeQtQml(QObject* parent = 0);
        ObjectLocatorNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        osgEarth::MapNodeQtQml* mapNode();
        QGeoCoordinate position() const;
        osg::NodeQtQml* object() const;
        QString url() const;

    public slots:
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);
        void setPosition(QGeoCoordinate position);
        void setObject(osg::NodeQtQml* object);
        void setUrl(QString objFile);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
        void positionChanged(QGeoCoordinate position);
        void objectChanged(osg::NodeQtQml* object);
        void urlChanged(QString objFile);
    };
}
}
#endif
