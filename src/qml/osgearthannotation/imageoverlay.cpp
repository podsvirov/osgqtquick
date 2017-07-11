#include "imageoverlay.hpp"
#include "imageoverlayindex.hpp"
#include <osgEarthAnnotation/ImageOverlay>

namespace osgEarth {
namespace Annotation {

    ImageOverlayQtQml::Index::Index(ImageOverlay* o)
        : AnnotationNodeQtQml::Index(o)
    {
    }

    void ImageOverlayQtQml::Index::classBegin()
    {
    }

    void ImageOverlayQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            osg::Image* image = osgDB::readImageFile(filename.toStdString());
            if (image) {
                ImageOverlay* imageOverlay = new ImageOverlay(mapNode, image);
                imageOverlay->setBounds(Bounds(bounds.x(), bounds.y(), bounds.z(), bounds.w()));
                setO(imageOverlay);
            }
        }
        AnnotationNodeQtQml::Index::componentComplete();
    }

    ImageOverlayQtQml::ImageOverlayQtQml(QObject* parent)
        : AnnotationNodeQtQml(parent)
    {
    }

    ImageOverlayQtQml::ImageOverlayQtQml(ImageOverlayQtQml::Index* index, QObject* parent)
        : AnnotationNodeQtQml(index, parent)
    {
    }

    void ImageOverlayQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        AnnotationNodeQtQml::classBegin();
    }

    void ImageOverlayQtQml::componentComplete()
    {
        AnnotationNodeQtQml::componentComplete();
    }

    osgEarth::MapNodeQtQml* ImageOverlayQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    QString ImageOverlayQtQml::filename() const
    {
        return i(this)->filename;
    }

    QVector4D ImageOverlayQtQml::bounds() const
    {
        return i(this)->bounds;
    }

    void ImageOverlayQtQml::setMapNode(osgEarth::MapNodeQtQml* mapNode)
    {
        if (!isComplete()) {
            i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
            return;
        }
        i(this)->mapNode = mapNode ? mapNode->mapNode() : 0;
        emit mapNodeChanged(mapNode);
    }

    void ImageOverlayQtQml::setFilename(QString filename)
    {
        if (!isComplete()) {
            i(this)->filename = filename;
            return;
        }

        i(this)->filename = filename;
        emit filenameChanged(filename);
    }

    void ImageOverlayQtQml::setBounds(QVector4D bounds)
    {
        if (!isComplete()) {
            i(this)->bounds = bounds;
            return;
        }

        i(this)->bounds = bounds;
        emit boundsChanged(bounds);
    }
}
}
