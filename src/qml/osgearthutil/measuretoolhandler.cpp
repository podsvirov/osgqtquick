#include "measuretoolhandler.hpp"
#include "measuretoolhandlerindex.hpp"

namespace osgEarth {
namespace Util {

    MeasureRecordQtQml::Index::Index(MeasureRecord* o)
        : osgQtQml::Index(o)
    {
    }

    void MeasureRecordQtQml::Index::classBegin()
    {
        if (!o(this))
            setO(new MeasureRecord);

        osgQtQml::Index::classBegin();
    }

    MeasureRecordQtQml::MeasureRecordQtQml(QObject* parent)
        : osgQtQml::Object(parent)
    {
    }

    MeasureRecordQtQml::MeasureRecordQtQml(MeasureRecordQtQml::Index* index, QObject* parent)
        : osgQtQml::Object(index, parent)
    {
    }

    MeasureRecord* MeasureRecordQtQml::measureRecord()
    {
        return o(this);
    }

    MeasureRecordQtQml* MeasureRecordQtQml::fromMeasureRecord(MeasureRecord* record, QObject* parent)
    {
        if (!record)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(record)) {
            return static_cast<MeasureRecordQtQml*>(index->qtObject());
        }

        MeasureRecordQtQml* result = new MeasureRecordQtQml(new Index(record), parent);
        result->classBegin();

        return result;
    }

    void MeasureRecordQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);

        i(this)->setQ(this);

        osgQtQml::Object::classBegin();
    }

    QVector3D MeasureRecordQtQml::start()
    {
        return osgQt::qVector3D(o(this)->start());
    }

    QVector3D MeasureRecordQtQml::end()
    {
        return osgQt::qVector3D(o(this)->end());
    }

    double MeasureRecordQtQml::distance()
    {
        return o(this)->distance();
    }

    SimpleMeasureToolCallback::SimpleMeasureToolCallback(MeasureToolHandlerQtQml* handler)
        : handlerQtQml(handler)
    {
    }

    void SimpleMeasureToolCallback::onDistanceChanged(MeasureToolHandlerEx* sender, double distance)
    {
        //        std::stringstream ss;
        //        ss << "Distance = " << std::setprecision(10) << distance << "m" << std::endl;
        //        std::string str;
        //        str = ss.str();
        handlerQtQml->getRecords().push_back(new MeasureRecord(sender->firstPos(), sender->secondPos(), distance));
        handlerQtQml->setDistance(distance);
        emit handlerQtQml->numRecordsChanged(handlerQtQml->getRecords().size());
        emit handlerQtQml->distanceChanged(distance);
    }
    MeasureToolHandlerQtQml::Index::Index(MeasureToolHandlerEx* handler)
        : osgGA::GUIEventHandlerQtQml::Index(handler)
        , path(false)
        , circle(true)
    {
    }
    void MeasureToolHandlerQtQml::Index::classBegin()
    {
    }

    void MeasureToolHandlerQtQml::Index::componentComplete()
    {
        if (!o(this) && mapNode && group) {
            MeasureToolHandlerEx* handler = new MeasureToolHandlerEx(group, mapNode);
            handler->setIsPath(path);
            handler->setGeoInterpolation(circle ? GEOINTERP_GREAT_CIRCLE : GEOINTERP_RHUMB_LINE);
            handler->addEventHandler(new SimpleMeasureToolCallback(q(this)));
            setO(handler);
        }
        osgGA::GUIEventHandlerQtQml::Index::componentComplete();
    }

    MeasureToolHandlerQtQml::MeasureToolHandlerQtQml(QObject* parent)
        : osgGA::GUIEventHandlerQtQml(parent)
    {
    }

    MeasureToolHandlerQtQml::MeasureToolHandlerQtQml(MeasureToolHandlerQtQml::Index* index, QObject* parent)
        : osgGA::GUIEventHandlerQtQml(index, parent)
    {
    }

    void MeasureToolHandlerQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);
        i(this)->setQ(this);
        osgGA::GUIEventHandlerQtQml::classBegin();
    }

    MeasureToolHandlerEx* MeasureToolHandlerQtQml::measureToolHandlerEx()
    {
        return o(this);
    }

    MeasureToolHandlerQtQml* MeasureToolHandlerQtQml::fromMeasureToolHandlerEx(MeasureToolHandlerEx* handler, QObject* parent)
    {
        if (!handler)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(handler)) {
            return static_cast<MeasureToolHandlerQtQml*>(index->qtObject());
        }

        return new MeasureToolHandlerQtQml(new Index(handler), parent);
    }

    bool MeasureToolHandlerQtQml::path() const
    {
        return o(this) ? o(this)->getIsPath() : i(this)->path;
    }

    bool MeasureToolHandlerQtQml::circle() const
    {
        return o(this) ? (o(this)->getGeoInterpolation() == GEOINTERP_GREAT_CIRCLE ? true : false) : (i(this)->circle);
    }

    osg::GroupQtQml* MeasureToolHandlerQtQml::group() const
    {
        return osg::GroupQtQml::fromGroup(i(this)->group);
    }

    MapNodeQtQml* MeasureToolHandlerQtQml::mapNode() const
    {
        return osgEarth::MapNodeQtQml::fromMapNode(i(this)->mapNode);
    }

    void MeasureToolHandlerQtQml::setDistance(double distance)
    {
        i(this)->distance = distance;
    }

    QQmlListProperty<MeasureRecordQtQml> MeasureToolHandlerQtQml::records()
    {
        return QQmlListProperty<MeasureRecordQtQml>(this, (void*)0,
            MeasureToolHandlerQtQml::recordsCount,
            MeasureToolHandlerQtQml::recordsAt);
    }

    int MeasureToolHandlerQtQml::getNumRecords()
    {
        return _records.size();
    }

    MeasureRecordQtQml* MeasureToolHandlerQtQml::getRecordAt(int index)
    {
        return MeasureRecordQtQml::fromMeasureRecord(_records[index]);
    }

    double MeasureToolHandlerQtQml::distance() const
    {
        return i(this)->distance;
    }

    void MeasureToolHandlerQtQml::setPath(bool path)
    {
        if (!isComplete()) {
            i(this)->path = path;
            return;
        }
        i(this)->path = path;
        o(this)->setIsPath(path);
    }

    void MeasureToolHandlerQtQml::setCircle(bool circle)
    {
        if (!isComplete()) {
            i(this)->circle = circle;
            return;
        }
        i(this)->circle = circle;
        o(this)->setGeoInterpolation(circle ? GEOINTERP_GREAT_CIRCLE : GEOINTERP_RHUMB_LINE);
    }

    void MeasureToolHandlerQtQml::setGroup(osg::GroupQtQml* group)
    {
        if (!isComplete()) {
            i(this)->group = group->group();
            return;
        }
        i(this)->group = group->group();
    }

    void MeasureToolHandlerQtQml::setMapNode(MapNodeQtQml* mapNode)
    {
        MapNode* _mapNode = mapNode->mapNode();
        if (!isComplete()) {
            i(this)->mapNode = _mapNode;
            return;
        }
        i(this)->mapNode = _mapNode;
        o(this)->setMapNode(_mapNode);
    }

    int MeasureToolHandlerQtQml::recordsCount(QQmlListProperty<MeasureRecordQtQml>* list)
    {
        return static_cast<MeasureToolHandlerQtQml*>(list->object)->getNumRecords();
    }

    MeasureRecordQtQml* MeasureToolHandlerQtQml::recordsAt(QQmlListProperty<MeasureRecordQtQml>* list, int index)
    {
        return static_cast<MeasureToolHandlerQtQml*>(list->object)->getRecordAt(index);
    }
}
}
