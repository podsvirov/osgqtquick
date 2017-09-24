#include "imagelayer.hpp"
#include "imagelayerindex.hpp"
#include <osgEarth/ImageLayer>

namespace osgEarth {
// ImageLayerQtQml
ImageLayerQtQml::Index::Index(ImageLayer* layer)
    : TerrainLayerQtQml::Index(layer)
    , hslFilter(nullptr)
    , rgbFilter(nullptr)
    , cmykFilter(nullptr)
    , bcFilter(nullptr)
    , gammaFilter(nullptr)
    , ckFilter(nullptr)
{
    useHSL = useRGB = useCMYK = useBC = useGamma = useChromaKey = false;
}

void ImageLayerQtQml::Index::classBegin()
{
    TerrainLayerQtQml::Index::classBegin();
}

QVector3D ImageLayerQtQml::Index::getHSLOffset()
{
    QVector3D qV3d;
    if (hslFilter) {
        qV3d = osgQt::qVector3D(hslFilter->getHSLOffset());
    }
    return qV3d;
}
QVector3D ImageLayerQtQml::Index::getRGBOffset()
{
    QVector3D qV3d;
    if (rgbFilter) {
        qV3d = osgQt::qVector3D(rgbFilter->getRGBOffset());
    }
    return qV3d;
}

QVector4D ImageLayerQtQml::Index::getCMYKOffset()
{
    QVector4D qV4d;
    if (cmykFilter) {
        qV4d = osgQt::qVector4D(cmykFilter->getCMYKOffset());
    }
    return qV4d;
}

QVector2D ImageLayerQtQml::Index::getBC()
{
    QVector2D qV2d;
    if (bcFilter) {
        qV2d = osgQt::qVector2D(bcFilter->getBrightnessContrast());
    }
    return qV2d;
}

QVector3D ImageLayerQtQml::Index::getGamma()
{
    QVector3D qV3d;
    if (gammaFilter) {
        qV3d = osgQt::qVector3D(gammaFilter->getGamma());
    }
    return qV3d;
}

QVector3D ImageLayerQtQml::Index::getCK()
{
    QVector3D qV3d;
    if (ckFilter) {
        qV3d = osgQt::qVector3D(ckFilter->getColor());
    }
    return qV3d;
}

bool ImageLayerQtQml::Index::setHSLOffset(const QVector3D& hsl)
{
    if (hslFilter) {
        hslFilter->setHSLOffset(osgQt::vec3d(hsl));
        return true;
    }
    return false;
}

bool ImageLayerQtQml::Index::setRGBOffset(const QVector3D& rgb)
{
    if (rgbFilter) {
        rgbFilter->setRGBOffset(osgQt::vec3d(rgb));
        return true;
    }
    return false;
}

bool ImageLayerQtQml::Index::setCMYKOffset(const QVector4D& cmyk)
{
    if (cmykFilter) {
        cmykFilter->setCMYKOffset(osgQt::vec4d(cmyk));
        return true;
    }
    return false;
}

bool ImageLayerQtQml::Index::setBC(const QVector2D& bc)
{
    if (bcFilter) {
        bcFilter->setBrightnessContrast(osgQt::vec2d(bc));
        return true;
    }
    return false;
}

bool ImageLayerQtQml::Index::setGamma(const QVector3D& gamma)
{
    if (gammaFilter) {
        gammaFilter->setGamma(osgQt::vec3d(gamma));
        return true;
    }
    return false;
}

bool ImageLayerQtQml::Index::setCK(const QVector3D& ck)
{
    if (ckFilter) {
        ckFilter->setColor(osgQt::vec3d(ck));
        return true;
    }
    return false;
}

void ImageLayerQtQml::Index::useFilter(Index::FilterType type, bool use)
{
    switch (type) {
    case HSL_FILTER: {
        if (use && !hslFilter) {
            hslFilter = new HSLColorFilter;
            o(this)->addColorFilter(hslFilter);
            setGamma(gamma);
        } else if (!use && hslFilter) {
            o(this)->removeColorFilter(hslFilter);
            hslFilter = nullptr;
        }
        break;
    }
    case RGB_FILTER: {
        if (use && !hslFilter) {
            rgbFilter = new RGBColorFilter;
            o(this)->addColorFilter(rgbFilter);
            setRGBOffset(rgbOffset);
        } else if (!use && rgbFilter) {
            o(this)->removeColorFilter(rgbFilter);
            rgbFilter = nullptr;
        }
        break;
    }
    case CMYK_FILTER: {
        if (use && !cmykFilter) {
            cmykFilter = new CMYKColorFilter;
            o(this)->addColorFilter(cmykFilter);
            setCMYKOffset(cmykOffset);
        } else if (!use && cmykFilter) {
            o(this)->removeColorFilter(cmykFilter);
            cmykFilter = nullptr;
        }
        break;
    }
    case BC_FILTER: {
        if (use && !bcFilter) {
            bcFilter = new BrightnessContrastColorFilter;
            o(this)->addColorFilter(bcFilter);
            setBC(bc);
        } else if (!use && bcFilter) {
            o(this)->removeColorFilter(bcFilter);
            bcFilter = nullptr;
        }
        break;
    }
    case GAMMA_FILTER: {
        if (use && !gammaFilter) {
            gammaFilter = new GammaColorFilter;
            o(this)->addColorFilter(gammaFilter);
            setGamma(gamma);
        } else if (!use && gammaFilter) {
            o(this)->removeColorFilter(gammaFilter);
            gammaFilter = nullptr;
        }
        break;
    }
    case CHROMAKEY_FILTER: {
        if (use && !ckFilter) {
            ckFilter = new ChromaKeyColorFilter;
            o(this)->addColorFilter(ckFilter);
            setCK(ck);
        } else if (!use && ckFilter) {
            o(this)->removeColorFilter(ckFilter);
            ckFilter = nullptr;
        }
        break;
    }
    default:
        break;
    }
}

ImageLayerQtQml::ImageLayerQtQml(QObject* parent)
    : TerrainLayerQtQml(parent)
{
}

ImageLayerQtQml::ImageLayerQtQml(ImageLayerQtQml::Index* index, QObject* parent)
    : TerrainLayerQtQml(index, parent)
{
}

void ImageLayerQtQml::classBegin()
{
    if (!i(this))
        setI(new Index);

    i(this)->setQ(this);

    TerrainLayerQtQml::classBegin();
}

float ImageLayerQtQml::opacity()
{
    return i(this)->opacity;
}

ImageLayer* ImageLayerQtQml::imageLayer()
{
    return o(this);
}

ImageLayerQtQml* ImageLayerQtQml::fromImageLayer(ImageLayer* layer, QObject* parent)
{
    if (!layer)
        return 0;

    if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(layer)) {
        return static_cast<ImageLayerQtQml*>(index->qtObject());
    }

    ImageLayerQtQml* result = new ImageLayerQtQml(new Index(layer), parent);
    result->classBegin();

    return result;
}

bool ImageLayerQtQml::useHSL() const
{
    return i(this)->useHSL;
}

bool ImageLayerQtQml::useRGB() const
{
    return i(this)->useRGB;
}

bool ImageLayerQtQml::useCMYK() const
{
    return i(this)->useCMYK;
}

bool ImageLayerQtQml::useBC() const
{
    return i(this)->useBC;
}

bool ImageLayerQtQml::useGamma() const
{
    return i(this)->useGamma;
}

bool ImageLayerQtQml::useChromaKey() const
{
    return i(this)->useChromaKey;
}

QVector3D ImageLayerQtQml::hslOffset()
{
    return i(this)->getHSLOffset();
}

QVector3D ImageLayerQtQml::rgbOffset()
{
    return i(this)->getRGBOffset();
}

QVector4D ImageLayerQtQml::cmykOffset()
{
    return i(this)->getCMYKOffset();
}

QVector2D ImageLayerQtQml::bc()
{
    return i(this)->getBC();
}

QVector3D ImageLayerQtQml::gamma()
{
    return i(this)->getGamma();
}

QVector3D ImageLayerQtQml::ck()
{
    return i(this)->getCK();
}

void ImageLayerQtQml::setOpacity(float opacity)
{
    if (!isComplete()) {
        i(this)->opacity = opacity;
        return;
    }
    i(this)->opacity = opacity;
    o(this)->setOpacity(opacity);
}

void ImageLayerQtQml::setUseHSL(bool useHSL)
{
    i(this)->useHSL = useHSL;
}

void ImageLayerQtQml::setUseRGB(bool useRGB)
{
    i(this)->useRGB = useRGB;
    if (!isComplete())
        return;
    i(this)->useFilter(Index::FilterType::RGB_FILTER, useRGB);
}

void ImageLayerQtQml::setUseCMYK(bool useCMYK)
{
    i(this)->useCMYK = useCMYK;
    if (!isComplete())
        return;
    i(this)->useFilter(Index::FilterType::CMYK_FILTER, useCMYK);
}

void ImageLayerQtQml::setUseBC(bool useBC)
{
    i(this)->useBC = useBC;
    if (!isComplete())
        return;
    i(this)->useFilter(Index::FilterType::BC_FILTER, useBC);
}

void ImageLayerQtQml::setUseGamma(bool useGamma)
{
    i(this)->useGamma = useGamma;
    if (!isComplete())
        return;
    i(this)->useFilter(Index::FilterType::GAMMA_FILTER, useGamma);
}

void ImageLayerQtQml::setUseChromaKey(bool useChromaKey)
{
    i(this)->useChromaKey = useChromaKey;
    if (!isComplete())
        return;
    i(this)->useFilter(Index::FilterType::CHROMAKEY_FILTER, useChromaKey);
}

void ImageLayerQtQml::setHslOffset(QVector3D hslOffset)
{
    i(this)->hslOffset = hslOffset;
    if (!isComplete())
        return;
    i(this)->setHSLOffset(hslOffset);
}

void ImageLayerQtQml::setRgbOffset(QVector3D rgbOffset)
{
    i(this)->rgbOffset = rgbOffset;
    if (!isComplete())
        return;
    i(this)->setRGBOffset(rgbOffset);
}

void ImageLayerQtQml::setCmykOffset(QVector4D cmykOffset)
{
    i(this)->cmykOffset = cmykOffset;
    if (!isComplete())
        return;
    i(this)->setCMYKOffset(cmykOffset);
}

void ImageLayerQtQml::setBc(QVector2D bc)
{
    i(this)->bc = bc;
    if (!isComplete())
        return;
    i(this)->setBC(bc);
}

void ImageLayerQtQml::setGamma(QVector3D gamma)
{
    i(this)->gamma = gamma;
    if (!isComplete())
        return;
    i(this)->setGamma(gamma);
}

void ImageLayerQtQml::setCk(QVector3D ck)
{
    i(this)->ck = ck;
    if (!isComplete())
        return;
    i(this)->setCK(ck);
}
}
