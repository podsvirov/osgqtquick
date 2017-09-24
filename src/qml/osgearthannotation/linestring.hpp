
#ifndef _OSGEARTH_SYMBOLOGY_LINE_STRING_QTQML_
#define _OSGEARTH_SYMBOLOGY_LINE_STRING_QTQML_ 1

#include <QColor>
#include <QVector3D>
#include <osg/GroupQtQml>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthAnnotation/AnnotationNodeQtQml>

namespace osgEarth {
namespace Annotation {
    class FeatureNode;
    class OSGQTQML_EXPORT LineStringQtQml : public AnnotationNodeQtQml {
        Q_OBJECT
    public:
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(QVector3D start READ start WRITE setStart NOTIFY startChanged)
        Q_PROPERTY(QVector3D end READ end WRITE setEnd NOTIFY endChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(double lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY(double pointSize READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)
        Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor NOTIFY pointColorChanged)

    public:
        class Index;
        LineStringQtQml(QObject* parent = 0);
        LineStringQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        QVector3D start() const;
        QVector3D end() const;
        QColor lineColor() const;
        double lineWidth() const;
        double pointSize() const;
        QColor pointColor() const;
        osg::GroupQtQml* parent() const;
        osgEarth::MapNodeQtQml* mapNode() const;

    public slots:
        void setStart(QVector3D start);
        void setEnd(QVector3D end);
        void setLineColor(QColor lineColor);
        void setLineWidth(double lineWidth);
        void setPointSize(double pointSize);
        void setPointColor(QColor pointColor);
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);

    signals:
        void startChanged(QVector3D start);
        void endChanged(QVector3D end);
        void lineColorChanged(QColor lineColor);
        void lineWidthChanged(double lineWidth);
        void pointSizeChanged(double pointSize);
        void pointColorChanged(QColor pointColor);
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);

    private:
    };
}
} // osgEarth::Symbology

#endif
