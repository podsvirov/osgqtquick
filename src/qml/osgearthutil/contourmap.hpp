#ifndef _OSGEARTHUTIL_CONTOUR_MAP_QTQML_
#define _OSGEARTHUTIL_CONTOUR_MAP_QTQML_ 1

#include <osgEarth/TerrainEffectQtQml>

namespace osgEarth {
namespace Util {
    class ContourMap;
    class OSGQTQML_EXPORT ContourMapQtQml : public TerrainEffectQtQml {
        Q_OBJECT
        Q_PROPERTY(float opacity READ opacity WRITE setOpacity)
        Q_PROPERTY(bool grayscale READ grayscale WRITE setGrayscale)

    public:
        class Index;
        ContourMapQtQml(QObject* parent = 0);
        ContourMapQtQml(Index* index, QObject* parent = 0);

        ContourMap* contourMap();

        void classBegin();

        float opacity() const;
        bool grayscale() const;

    public slots:
        void setOpacity(float opacity);
        void setGrayscale(bool grayscale);
    };
}
}

#endif
