#ifndef _OSGEARTH_ANNO_PLACE_NODE_QTQML_
#define _OSGEARTH_ANNO_PLACE_NODE_QTQML_ 1

#include <QColor>
#include <osgEarthAnnotation/GeoPositionNodeQtQml>

namespace osgEarth {
namespace Annotation {
    class PlaceNode;
    class OSGQTQML_EXPORT PlaceNodeQtQml : public GeoPositionNodeQtQml {
        Q_OBJECT
        Q_PROPERTY(QString text READ text WRITE setText)
        Q_PROPERTY(QString styleUrl READ styleUrl WRITE setStyleUrl)
        Q_PROPERTY(QColor styleHalo READ styleHalo WRITE setStyleHalo)

    public:
        class Index;
        PlaceNodeQtQml(QObject* parent = 0);
        PlaceNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        QString styleUrl() const;
        QColor styleHalo() const;
        QString text() const;

        PlaceNode* placeNode();

        static PlaceNodeQtQml* fromPlaceNode(PlaceNode* placeNode, QObject* parent = 0);

    public slots:
        void setStyleUrl(QString styleUrl);
        void setStyleHalo(QColor styleHalo);
        void setText(QString text);
    };
}
} // namespace osgEarth::Annotation

#endif
