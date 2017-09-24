
#include "placenode.hpp"
#include "placenodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthSymbology/GeometryFactory>

namespace osgEarth {
namespace Annotation {

    PlaceNodeQtQml::Index::Index(PlaceNode* placeNode)
        : GeoPositionNodeQtQml::Index(placeNode)
        , styleHalo(QColor("#FF5F5F5F"))
    {
    }

    void PlaceNodeQtQml::Index::classBegin()
    {
    }

    void PlaceNodeQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            style.getOrCreate<IconSymbol>()->url()->setLiteral(styleUrl.toStdString());
            style.getOrCreate<IconSymbol>()->declutter() = true;
            style.getOrCreate<TextSymbol>()->halo() = Stroke(osgQt::swapColor(styleHalo));
            const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
            GeoPoint point = GeoPoint(geoSRS, osgQt::vec3d(position));
            PlaceNode* placeNode = new PlaceNode(mapNode, point, text.toStdString(), style);

            setO(placeNode);
        }
        GeoPositionNodeQtQml::Index::componentComplete();
    }

    PlaceNodeQtQml::PlaceNodeQtQml(QObject* parent)
        : GeoPositionNodeQtQml(parent)
    {
    }

    PlaceNodeQtQml::PlaceNodeQtQml(PlaceNodeQtQml::Index* index, QObject* parent)
        : GeoPositionNodeQtQml(index, parent)
    {
    }

    void PlaceNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        GeoPositionNodeQtQml::classBegin();
    }

    QString PlaceNodeQtQml::styleUrl() const
    {
        return i(this)->styleUrl;
    }

    QColor PlaceNodeQtQml::styleHalo() const
    {
        return i(this)->styleHalo;
    }

    QString PlaceNodeQtQml::text() const
    {
        return i(this)->text;
    }

    PlaceNode* PlaceNodeQtQml::placeNode()
    {
        return o(this);
    }

    PlaceNodeQtQml* PlaceNodeQtQml::fromPlaceNode(PlaceNode* placeNode, QObject* parent)
    {
        if (!placeNode)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(placeNode)) {
            return static_cast<PlaceNodeQtQml*>(index->qtObject());
        }

        PlaceNodeQtQml* result = new PlaceNodeQtQml(new Index(placeNode), parent);
        result->classBegin();
        result->componentComplete();
        return result;
    }

    void PlaceNodeQtQml::setStyleUrl(QString styleUrl)
    {
        if (!isComplete()) {
            i(this)->styleUrl = styleUrl;
            return;
        }
        i(this)->styleUrl = styleUrl;
    }

    void PlaceNodeQtQml::setStyleHalo(QColor styleHalo)
    {
        if (!isComplete()) {
            i(this)->styleHalo = styleHalo;
            return;
        }
        i(this)->styleHalo = styleHalo;
    }

    void PlaceNodeQtQml::setText(QString text)
    {
        i(this)->text = text;
        if (!isComplete())
            return;
        o(this)->setText(text.toUtf8().toStdString());
    }
}
}
