#ifndef _OSGEARTH_ANNO_IMAGE_OVERLAY_QTQML_
#define _OSGEARTH_ANNO_IMAGE_OVERLAY_QTQML_ 1

#include <QVector4D>
#include <osg/GroupQtQml>
#include <osg/NodeQtQml>
#include <osgEarth/MapNodeQtQml>
#include <osgEarthAnnotation/AnnotationNodeQtQml>
#include <osgEarthAnnotation/ImageOverlay>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT ImageOverlayQtQml : public AnnotationNodeQtQml {
    public:
        Q_OBJECT
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode NOTIFY mapNodeChanged)
        Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
        Q_PROPERTY(QVector4D bounds READ bounds WRITE setBounds NOTIFY boundsChanged)

    public:
        class Index;
        ImageOverlayQtQml(QObject* parent = 0);
        ImageOverlayQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();
        virtual void componentComplete();

        osgEarth::MapNodeQtQml* mapNode() const;
        QString filename() const;
        QVector4D bounds() const;

    public slots:
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);
        void setFilename(QString filename);
        void setBounds(QVector4D bounds);

    signals:
        void mapNodeChanged(osgEarth::MapNodeQtQml* mapNode);
        void filenameChanged(QString filename);
        void boundsChanged(QVector4D bounds);
    };
}
}
#endif
