#ifndef _OSGEARTH_ANNO_LABEL_NODE_QTQML_
#define _OSGEARTH_ANNO_LABEL_NODE_QTQML_ 1

#include "../osg/group.hpp"
#include <QColor>
#include <QGeoCoordinate>
#include <QVector2D>
#include <osg/NodeQtQml>
#include <osgEarthAnnotation/GeoPositionNodeQtQml>
#include <osgEarthAnnotation/LabelNode>

namespace osgEarth {
namespace Annotation {
    class LabelNode;
    class OSGQTQML_EXPORT LabelNodeQtQml : public GeoPositionNodeQtQml {
    public:
        Q_OBJECT
        Q_PROPERTY(QColor styleColor READ styleColor WRITE setStyleColor NOTIFY styleColorChanged)
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

    public:
        class Index;
        LabelNodeQtQml(QObject* parent = 0);
        LabelNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

    public:
        QColor styleColor() const;
        QString text() const;

    public slots:
        void setStyleColor(QColor styleColor);
        void setText(QString text);

    signals:
        void styleColorChanged(QColor styleColor);
        void textChanged(QString text);

    private:
    };
}
}

#endif
