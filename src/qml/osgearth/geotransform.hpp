#ifndef _OSGEARTH_GEOTRANSFORM_QTQML_
#define _OSGEARTH_GEOTRANSFORM_QTQML_ 1

#include <QGeoCoordinate>
#include <osg/MatrixTransformQtQml>
#include <osgEarth/MapNodeQtQml>

namespace osgEarth {
class GeoTransform;
class OSGQTQML_EXPORT GeoTransformQtQml : public osg::MatrixTransformQtQml {
    Q_OBJECT

public:
    Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)

public:
    class Index;
    GeoTransformQtQml(QObject* parent = 0);
    GeoTransformQtQml(Index*, QObject* parent = 0);

    void classBegin();
    void componentComplete();

    osgEarth::MapNodeQtQml* mapNode() const;
    QGeoCoordinate position() const;

    GeoTransform* geoTransform();

    static GeoTransformQtQml* fromGeoTransform(GeoTransform* transform, QObject* parent = 0);

public slots:
    void setMapNode(osgEarth::MapNodeQtQml* mapNode);
    void setPosition(QGeoCoordinate position);

signals:
    void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
    void positionChanged(QGeoCoordinate geoCoord);
};
}

#endif
