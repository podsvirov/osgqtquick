#ifndef _OSGEARTHUTIL_MEASURETOOL_QTQML_
#define _OSGEARTHUTIL_MEASURETOOL_QTQML_ 1

#include "measuretoolex.hpp"
#include <QVector3D>
#include <osg/GroupQtQml>
#include <osg/ObjectQtQml>
#include <osgEarth/MapNodeQtQml>
#include <osgGA/GUIEventHandlerQtQml>

namespace osgEarth {
namespace Util {
    // MeasureRecord
    struct MeasureRecord : osg::Referenced {
        MeasureRecord() = default;
        MeasureRecord(const osg::Vec3& start, const osg::Vec3& end, double distance)
            : _start(start)
            , _end(end)
            , _distance(distance)
        {
        }

        osg::Vec3& start() { return _start; }
        osg::Vec3& end() { return _end; }
        double distance() { return _distance; }

        osg::Vec3 _start;
        osg::Vec3 _end;
        double _distance;
    };

    // MeasureRecordQtQml
    class OSGQTQML_EXPORT MeasureRecordQtQml : public osgQtQml::Object {
        Q_OBJECT
        Q_PROPERTY(QVector3D start READ start)
        Q_PROPERTY(QVector3D end READ end)
        Q_PROPERTY(double distance READ distance)

    public:
        class Index;
        MeasureRecordQtQml(QObject* parent = 0);
        MeasureRecordQtQml(Index* index, QObject* parent = 0);

        void classBegin();

        QVector3D start();
        QVector3D end();
        double distance();

        MeasureRecord* measureRecord();
        static MeasureRecordQtQml* fromMeasureRecord(MeasureRecord* record, QObject* parent = 0);
    };

    typedef std::vector<osg::ref_ptr<MeasureRecord> > MeasureRecords;

    class MeasureToolHandlerQtQml;
    // SimpleMeasureToolCallback
    class SimpleMeasureToolCallback : public MeasureToolHandlerEx::MeasureToolEventHandler {
    public:
        SimpleMeasureToolCallback(MeasureToolHandlerQtQml* handlerQtQml);
        virtual void onDistanceChanged(MeasureToolHandlerEx* sender, double distance);

    private:
        MeasureToolHandlerQtQml* handlerQtQml;
    };

    class MeasureToolHandlerEx;
    // MeasureToolHandlerQtQml
    class OSGQTQML_EXPORT MeasureToolHandlerQtQml : public osgGA::GUIEventHandlerQtQml {
        Q_OBJECT
        Q_PROPERTY(osg::GroupQtQml* group READ group WRITE setGroup)
        Q_PROPERTY(MapNodeQtQml* mapNode READ mapNode WRITE setMapNode)
        Q_PROPERTY(bool path READ path WRITE setPath)
        Q_PROPERTY(bool circle READ circle WRITE setCircle)
        Q_PROPERTY(double distance READ distance NOTIFY distanceChanged)

        Q_PROPERTY(int numRecords READ getNumRecords NOTIFY numRecordsChanged)
        Q_PROPERTY(QQmlListProperty<osgEarth::Util::MeasureRecordQtQml> records READ records NOTIFY numRecordsChanged)

    public:
        class Index;
        MeasureToolHandlerQtQml(QObject* parent = 0);
        MeasureToolHandlerQtQml(Index* index, QObject* parent = 0);
        virtual void classBegin();

        MeasureToolHandlerEx* measureToolHandlerEx();
        static MeasureToolHandlerQtQml* fromMeasureToolHandlerEx(MeasureToolHandlerEx* handler, QObject* parent = 0);

        bool path() const;
        bool circle() const;
        double distance() const;
        osg::GroupQtQml* group() const;
        MapNodeQtQml* mapNode() const;
        void setDistance(double distance);

        QQmlListProperty<osgEarth::Util::MeasureRecordQtQml> records();
        Q_INVOKABLE int getNumRecords();
        Q_INVOKABLE MeasureRecordQtQml* getRecordAt(int index);

        MeasureRecords& getRecords() { return _records; }

    private:
        MeasureRecords _records;

    public slots:
        void setPath(bool path);
        void setCircle(bool circle);
        void setGroup(osg::GroupQtQml* group);
        void setMapNode(MapNodeQtQml* mapNode);
    signals:
        void distanceChanged(double distance);
        void numRecordsChanged(int num);

    protected:
        static int recordsCount(QQmlListProperty<osgEarth::Util::MeasureRecordQtQml>* list);
        static MeasureRecordQtQml* recordsAt(QQmlListProperty<osgEarth::Util::MeasureRecordQtQml>* list, int index);
    };
}
}

#endif
