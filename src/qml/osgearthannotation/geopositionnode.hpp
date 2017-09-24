#ifndef _OSGEARTH_ANNO_ORTHO_NODE_QTQML_
#define _OSGEARTH_ANNO_ORTHO_NODE_QTQML_

#include <QGeoCoordinate>
#include <osg/NodeQtQml>
#include <osgEarth/GeoTransformQtQml>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthAnnotation/AnnotationNodeQtQml>

namespace osgEarth {
namespace Annotation {
    class GeoPositionNode;
    class OSGQTQML_EXPORT GeoPositionNodeQtQml : public AnnotationNodeQtQml {
        Q_OBJECT

        Q_PROPERTY(osgEarth::GeoTransformQtQml* geoTransform READ geoTransform)
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition)

    public:
        class Index;
        GeoPositionNodeQtQml(QObject* parent = 0);
        GeoPositionNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        Q_INVOKABLE osgEarth::GeoTransformQtQml* geoTransform();
        QGeoCoordinate position() const;
        osgEarth::MapNodeQtQml* mapNode() const;

    public slots:
        void setPosition(QGeoCoordinate position);
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
    };
}
} // osgEarth::Annotation
#endif
