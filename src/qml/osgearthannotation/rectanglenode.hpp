#ifndef OSGEARTH_ANNOTATION_RECTANGLE_QTQTML_
#define OSGEARTH_ANNOTATION_RECTANGLE_QTQTML_ 1

#include <QColor>
#include <QVector2D>
#include <osgEarthAnnotation/GeoPositionNodeQtQml>

namespace osgEarth {
namespace Annotation {
    class RectangleNode;
    class OSGQTQML_EXPORT RectangleNodeQtQml : public GeoPositionNodeQtQml {
    public:
        Q_OBJECT
        Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
        Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged)
        Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged)

    public:
        class Index;
        RectangleNodeQtQml(QObject* parent = 0);
        RectangleNodeQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        double width() const;
        double height() const;
        QColor fillColor() const;

    public slots:
        void setWidth(double width);
        void setHeight(double height);
        void setFillColor(QColor fillColor);

    signals:
        void widthChanged(double width);
        void heightChanged(double height);
        void fillColorChanged(QColor fillColor);
    };
}
}

#endif
