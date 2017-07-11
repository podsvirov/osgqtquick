#ifndef _OSGEARTH_IMAGE_LAYER_QTQML_
#define _OSGEARTH_IMAGE_LAYER_QTQML_ 1

#include "terrainlayer.hpp"

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

namespace osgEarth {
class ImageLayer;
// ImageLayer
class OSGQTQML_EXPORT ImageLayerQtQml : public TerrainLayerQtQml {
    Q_OBJECT
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(bool useHSL READ useHSL WRITE setUseHSL)
    Q_PROPERTY(bool useRGB READ useRGB WRITE setUseRGB)
    Q_PROPERTY(bool useCMYK READ useCMYK WRITE setUseCMYK)
    Q_PROPERTY(bool useBC READ useBC WRITE setUseBC)
    Q_PROPERTY(bool useGamma READ useGamma WRITE setUseGamma)
    Q_PROPERTY(bool useChromaKey READ useChromaKey WRITE setUseChromaKey)

    Q_PROPERTY(QVector3D hslOffset READ hslOffset WRITE setHslOffset)
    Q_PROPERTY(QVector3D rgbOffset READ rgbOffset WRITE setRgbOffset)
    Q_PROPERTY(QVector4D cmykOffset READ cmykOffset WRITE setCmykOffset)
    Q_PROPERTY(QVector2D bc READ bc WRITE setBc)
    Q_PROPERTY(QVector3D gamma READ gamma WRITE setGamma)
    Q_PROPERTY(QVector3D ck READ ck WRITE setCk)

public:
    class Index;
    ImageLayerQtQml(QObject* parent = 0);
    ImageLayerQtQml(Index* index, QObject* parent = 0);

    void classBegin();

    float opacity();

    ImageLayer* imageLayer();
    static ImageLayerQtQml* fromImageLayer(ImageLayer* layer, QObject* parent = 0);

    bool useHSL() const;
    bool useRGB() const;
    bool useCMYK() const;
    bool useBC() const;
    bool useGamma() const;
    bool useChromaKey() const;

    QVector3D hslOffset();
    QVector3D rgbOffset();
    QVector4D cmykOffset();
    QVector2D bc();
    QVector3D gamma();
    QVector3D ck();

public slots:
    void setOpacity(float opacity);
    void setUseHSL(bool useHSL);
    void setUseRGB(bool useRGB);
    void setUseCMYK(bool useCMYK);
    void setUseBC(bool useBC);
    void setUseGamma(bool useGamma);
    void setUseChromaKey(bool useChromaKey);
    void setHslOffset(QVector3D hslOffset);
    void setRgbOffset(QVector3D rgbOffset);
    void setCmykOffset(QVector4D cmykOffset);
    void setBc(QVector2D bc);
    void setGamma(QVector3D gamma);
    void setCk(QVector3D ck);
};
}

#endif
