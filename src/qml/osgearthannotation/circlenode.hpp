

#ifndef _OSGEARTH_ANNO_CIRCLE_NODE_QTQML_
#define _OSGEARTH_ANNO_CIRCLE_NODE_QTQML_ 1

#include <QColor>
#include <QVector3D>
#include <osg/GroupQtQml>
#include <osg/NodeQtQml>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/GeoPositionNodeQtQml>

namespace osgEarth {
namespace Annotation {

    class OSGQTQML_EXPORT CircleNodeQtQml : public GeoPositionNodeQtQml {
        Q_OBJECT

    public:
        Q_PROPERTY(QColor styleColor READ styleColor WRITE setStyleColor NOTIFY styleColorChanged)
        Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)
        Q_PROPERTY(double arcStart READ arcStart WRITE setArcStart NOTIFY arcStartChanged)
        Q_PROPERTY(double arcEnd READ arcEnd WRITE setArcEnd NOTIFY arcEndChanged)

    public:
        class Index;

        CircleNodeQtQml(QObject* parent = 0);
        CircleNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        QColor styleColor() const;
        double radius() const;
        double arcStart() const;
        double arcEnd() const;

    public slots:
        void setStyleColor(QColor styleColor);
        void setRadius(double radius);
        void setArcStart(double arcStart);
        void setArcEnd(double arcEnd);

    signals:
        void styleColorChanged(QColor styleColor);
        void radiusChanged(double radius);
        void arcStartChanged(double arcStart);
        void arcEndChanged(double arcEnd);
    };
}
} // namespace osgEarth::Annotation

#endif
