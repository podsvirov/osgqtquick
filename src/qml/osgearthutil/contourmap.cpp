#include "contourmap.hpp"
#include "contourmapindex.hpp"
#include <osgEarthUtil/ContourMap>

namespace osgEarth {
namespace Util {

    ContourMapQtQml::Index::Index(ContourMap* o)
        : osgEarth::TerrainEffectQtQml::Index(o)
        , opacity(1.0f)
        , grayscale(false)
    {
    }

    void ContourMapQtQml::Index::classBegin()
    {
        if (!o(this)) {
            ContourMap* cm = new ContourMap();
            cm->opacity() = opacity;
            cm->grayscale() = grayscale;
            cm->dirty();
            setO(cm);
        }

        osgEarth::TerrainEffectQtQml::Index::classBegin();
    }

    ContourMapQtQml::ContourMapQtQml(QObject* parent)
        : osgEarth::TerrainEffectQtQml(parent)
    {
    }

    ContourMapQtQml::ContourMapQtQml(ContourMapQtQml::Index* index, QObject* parent)
        : osgEarth::TerrainEffectQtQml(index, parent)
    {
    }

    ContourMap* ContourMapQtQml::contourMap()
    {
        return o(this);
    }

    void ContourMapQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);

        osgEarth::TerrainEffectQtQml::classBegin();
    }

    float ContourMapQtQml::opacity() const
    {
        return o(this) ? o(this)->opacity().value() : i(this)->opacity;
    }

    bool ContourMapQtQml::grayscale() const
    {
        return o(this) ? o(this)->grayscale().value() : i(this)->grayscale;
    }

    void ContourMapQtQml::setOpacity(float opacity)
    {
        if (!isComplete()) {
            i(this)->opacity = opacity;
            return;
        }
        i(this)->opacity = opacity;
        o(this)->opacity() = opacity;
        o(this)->dirty();
    }

    void ContourMapQtQml::setGrayscale(bool grayscale)
    {
        if (!isComplete()) {
            i(this)->grayscale = grayscale;
            return;
        }
        i(this)->grayscale = grayscale;
        o(this)->grayscale() = grayscale;
        o(this)->dirty();
    }
}
}
