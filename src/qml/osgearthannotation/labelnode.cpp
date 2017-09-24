#include "labelnode.hpp"
#include "labelnodeindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarthSymbology/Style>

namespace osgEarth {
namespace Annotation {

    LabelNodeQtQml::Index::Index(LabelNode* o)
        : GeoPositionNodeQtQml::Index(o)
        , styleColor(Qt::yellow)
    {
    }
    void LabelNodeQtQml::Index::classBegin()
    {
    }

    void LabelNodeQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode) {
            style.getOrCreate<TextSymbol>()->alignment() = TextSymbol::ALIGN_CENTER_CENTER;
            style.getOrCreate<TextSymbol>()->fill()->color() = osgQt::swapColor(styleColor);
            const osgEarth::SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
            LabelNode* labelNode = new LabelNode(mapNode, GeoPoint(geoSRS, osgQt::vec3d(position)), text.toStdString(), style);
            setO(labelNode);
        }
        GeoPositionNodeQtQml::Index::componentComplete();
    }

    LabelNodeQtQml::LabelNodeQtQml(QObject* parent)
        : GeoPositionNodeQtQml(parent)
    {
    }

    LabelNodeQtQml::LabelNodeQtQml(LabelNodeQtQml::Index* index, QObject* parent)
        : GeoPositionNodeQtQml(index, parent)
    {
    }

    void LabelNodeQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);
        GeoPositionNodeQtQml::classBegin();
    }

    QColor LabelNodeQtQml::styleColor() const
    {
        return i(this)->styleColor;
    }

    QString LabelNodeQtQml::text() const
    {
        return i(this)->text;
    }

    void LabelNodeQtQml::setStyleColor(QColor styleColor)
    {
        if (!isComplete()) {
            i(this)->styleColor = styleColor;
            return;
        }

        i(this)->styleColor = styleColor;

        emit styleColorChanged(styleColor);
    }

    void LabelNodeQtQml::setText(QString text)
    {
        if (!isComplete()) {
            i(this)->text = text;
            return;
        }

        i(this)->text = text;

        emit textChanged(text);
    }
}
}
