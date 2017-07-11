#include "verticalscale.hpp"
#include "verticalscaleindex.hpp"
#include <osgEarth/MapNode>
#include <osgEarth/TerrainEngineNode>
#include <osgEarthUtil/VerticalScale>

namespace osgEarth {
namespace Util {

    VerticalScaleQtQml::Index::Index(VerticalScale* o)
        : osgEarth::TerrainEffectQtQml::Index(o)
    {
    }

    void VerticalScaleQtQml::Index::classBegin()
    {
        if (!o(this))
            setO(new VerticalScale());
        osgEarth::TerrainEffectQtQml::Index::classBegin();
    }

    VerticalScaleQtQml::VerticalScaleQtQml(QObject* parent)
        : osgEarth::TerrainEffectQtQml(parent)
    {
        //m_scaler = new VerticalScale();
    }

    VerticalScaleQtQml::VerticalScaleQtQml(Index* index, QObject* parent)
        : osgEarth::TerrainEffectQtQml(index, parent)
    {
    }

    //    VerticalScaleQtQml::~VerticalScaleQtQml()
    //    {
    //        //    if (_scaler) delete _scaler;
    //    }

    float VerticalScaleQtQml::scale() const
    {
        return o(this)->getScale();
    }

    VerticalScale* VerticalScaleQtQml::verticalScale()
    {
        return o(this);
    }

    void VerticalScaleQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);

        osgEarth::TerrainEffectQtQml::classBegin();
    }

    void VerticalScaleQtQml::setScale(float scale)
    {
        if (!isComplete()) {
            i(this)->scale = scale;
            return;
        }
        i(this)->scale = scale;
        o(this)->setScale(scale);
    }
}
}
