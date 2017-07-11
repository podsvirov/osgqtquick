#ifndef _OSGEARTH_ANNOTATION_ELLIPSE_NODE_QTQML_
#define _OSGEARTH_ANNOTATION_ELLIPSE_NODE_QTQML_ 1

#include <QColor>
#include <QVector3D>
#include <osg/GroupQtQml>
#include <osg/NodeQtQml>
#include <osgEarthAnnotation/EllipseNode>
#include <osgEarthAnnotation/GeoPositionNodeQtQml>

namespace osgEarth {
namespace Annotation {
    class OSGQTQML_EXPORT EllipseNodeQtQml : public GeoPositionNodeQtQml {
        Q_OBJECT

    public:
        Q_PROPERTY(QColor styleColor READ styleColor WRITE setStyleColor NOTIFY styleColorChanged)
        Q_PROPERTY(double radiusMajor READ radiusMajor WRITE setRadiusMajor NOTIFY radiusMajorChanged)
        Q_PROPERTY(double radiusMinor READ radiusMinor WRITE setRadiusMinor NOTIFY radiusMinorChanged)
        Q_PROPERTY(double rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)
        Q_PROPERTY(double arcStart READ arcStart WRITE setArcStart NOTIFY arcStartChanged)
        Q_PROPERTY(double arcEnd READ arcEnd WRITE setArcEnd NOTIFY arcEndChanged)
        Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged)

    public:
        class Index;
        EllipseNodeQtQml(QObject* parent = 0);
        EllipseNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        QColor styleColor() const;
        double radiusMajor() const;
        double arcStart() const;
        double arcEnd() const;
        double radiusMinor() const;
        double rotationAngle() const;
        double height() const;

    public slots:
        void setStyleColor(QColor styleColor);
        void setRadiusMajor(double radius);
        void setArcStart(double arcStart);
        void setArcEnd(double arcEnd);
        void setRadiusMinor(double radiusMinor);
        void setRotationAngle(double rotationAngle);
        void setHeight(double height);

    signals:
        void styleColorChanged(QColor styleColor);
        void radiusMajorChanged(double radiusMajor);
        void arcStartChanged(double arcStart);
        void arcEndChanged(double arcEnd);
        void radiusMinorChanged(double radiusMinor);
        void rotationAngleChanged(double rotationAngle);
        void heightChanged(double height);
    };
}
}

#endif
