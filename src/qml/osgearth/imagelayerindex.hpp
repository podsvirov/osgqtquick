#ifndef _OSGEARTH_IMAGE_LAYER_QTQML_INDEX_
#define _OSGEARTH_IMAGE_LAYER_QTQML_INDEX_ 1

#include "imagelayer.hpp"
#include "terrainlayerindex.hpp"

#include <osgEarthSymbology/Color>
#include <osgEarthUtil/BrightnessContrastColorFilter>
#include <osgEarthUtil/CMYKColorFilter>
#include <osgEarthUtil/ChromaKeyColorFilter>
#include <osgEarthUtil/GammaColorFilter>
#include <osgEarthUtil/HSLColorFilter>
#include <osgEarthUtil/RGBColorFilter>

using namespace osgEarth::Util;

namespace osgEarth {
// ImageLayerQtQml::Index
class OSGQTQML_EXPORT ImageLayerQtQml::Index : public TerrainLayerQtQml::Index {
public:
    enum FilterType {
        HSL_FILTER,
        RGB_FILTER,
        CMYK_FILTER,
        BC_FILTER,
        GAMMA_FILTER,
        CHROMAKEY_FILTER
    };
    typedef ImageLayer OType;
    typedef ImageLayerQtQml QType;
    friend class ImageLayerQtQml;

public:
    Index(ImageLayer* o = 0);
    void classBegin();

    void useFilter(FilterType type, bool use);

    bool setHSLOffset(const QVector3D& hsl);
    QVector3D getHSLOffset();
    bool setRGBOffset(const QVector3D& rgb);
    QVector3D getRGBOffset();
    bool setCMYKOffset(const QVector4D& cmyk);
    QVector4D getCMYKOffset();
    bool setBC(const QVector2D& bc);
    QVector2D getBC();
    bool setGamma(const QVector3D& gamma);
    QVector3D getGamma();
    bool setCK(const QVector3D& ck);
    QVector3D getCK();

private:
    float opacity;
    bool useHSL;
    bool useRGB;
    bool useCMYK;
    bool useBC;
    bool useGamma;
    bool useChromaKey;

    QVector3D hslOffset;
    QVector3D rgbOffset;
    QVector4D cmykOffset;
    QVector2D bc;
    QVector3D gamma;
    QVector3D ck;

    HSLColorFilter* hslFilter;
    RGBColorFilter* rgbFilter;
    CMYKColorFilter* cmykFilter;
    BrightnessContrastColorFilter* bcFilter;
    GammaColorFilter* gammaFilter;
    ChromaKeyColorFilter* ckFilter;
};
}

#endif
