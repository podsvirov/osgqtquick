#ifndef _OSGEARTHUTIL_GEODETICGRATICULE_QTQML_
#define _OSGEARTHUTIL_GEODETICGRATICULE_QTQML_ 1

#include <QColor>
#include <osg/GroupQtQml>
#include <osgEarth/MapNodeQtQml>

namespace osgEarth {
namespace Util {
    class GraticuleNode;
    class OSGQTQML_EXPORT GeodeticGraticuleQtQml : public osg::GroupQtQml {
        Q_OBJECT
        Q_PROPERTY(osgEarth::MapNodeQtQml* mapNode READ mapNode WRITE setMapNode)
        Q_PROPERTY(osg::GroupQtQml* parent READ parent WRITE setParent)
        Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    public:
        class Index;
        GeodeticGraticuleQtQml(QObject* parent = 0);
        GeodeticGraticuleQtQml(Index* index, QObject* parent = 0);

        virtual void classBegin();

        osgEarth::MapNodeQtQml* mapNode() const;
        osg::GroupQtQml* parent() const;
        QColor color() const;
        bool visible() const;

    public slots:
        void setMapNode(osgEarth::MapNodeQtQml* mapNode);
        void setParent(osg::GroupQtQml* parent);
        void setColor(QColor color);
        void setVisible(bool visible);

    signals:
        void colorChanged(QColor color);
        void visibleChanged(bool visible);
    };
}
}

#endif
