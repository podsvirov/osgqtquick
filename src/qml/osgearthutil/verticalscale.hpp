
#ifndef _OSGEARTHUTIL_VERTICAL_SCALE_QTQML_
#define _OSGEARTHUTIL_VERTICAL_SCALE_QTQML_ 1

#include <osgEarth/TerrainEffectQtQml>

namespace osgEarth {
namespace Util {
    class VerticalScale;
    class OSGQTQML_EXPORT VerticalScaleQtQml : public TerrainEffectQtQml {
        Q_OBJECT
        //        Q_PROPERTY(osg::GroupQtQml* mapNode READ mapNode WRITE setMapNode)
        Q_PROPERTY(float scale READ scale WRITE setScale)

    public:
        class Index;
        VerticalScaleQtQml(QObject* parent = 0);
        VerticalScaleQtQml(Index* index, QObject* parent = 0);

        float scale() const;
        VerticalScale* verticalScale();

        void classBegin();

    public slots:
        void setScale(float scale);
    };
}
}

#endif
