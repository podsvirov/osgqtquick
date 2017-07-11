#ifndef _OSGEARTH_ANNO_MODEL_NODE_QTQML_
#define _OSGEARTH_ANNO_MODEL_NODE_QTQML_ 1

#include "geopositionnode.hpp"
#include <QGeoCoordinate>
#include <osg/GroupQtQml>
#include <osg/NodeQtQml>
#include <osg/ObjectQtQml>
#include <osg/ObjectQtQmlIndex>
#include <osgEarth/GeoData>
#include <osgEarth/ScreenSpaceLayout>
#include <osgEarthAnnotation/GeoPositionNodeQtQml>
#include <osgEarthAnnotation/ModelNode>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT ModelNodeQtQml : public GeoPositionNodeQtQml {
        Q_OBJECT
    public:
        Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

    public:
        class Index;

        ModelNodeQtQml(QObject* parent = 0);
        ModelNodeQtQml(Index* index, QObject* parent = 0);
        virtual void classBegin();
        virtual void componentComplete();

        QString url() const;
        ModelNode* modelNode();
        static ModelNodeQtQml* fromModelNode(ModelNode* node, QObject* parent = 0);
        QString label() const;

    public slots:
        void setUrl(QString url);
        void setLabel(QString label);

    signals:
        void urlChanged(QString url);
        void labelChanged(QString label);

    private:
        osgEarth::Annotation::ModelNode* m_modelNode;
    };
}
} // namespace osgEarth::Annotation

#endif // _OSGEARTH_ANNO_MODEL_NODE_QTQML_
