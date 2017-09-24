#include "activitymonitortool.hpp"
#include "activitymonitortoolindex.hpp"
#include <osgEarth/Registry>

namespace osgEarth {
namespace Util {

    ActivityMonitorTool::ActivityMonitorTool(ActivityMonitorToolQtQml* q)
        : _q(q)
    {
    }

    bool ActivityMonitorTool::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
    {
        if (ea.getEventType() == ea.FRAME) {
            std::set<std::string> activity;
            Registry::instance()->getActivities(activity);
            if (activity != _prev) {
                _activities.clear();
                for (std::set<std::string>::const_iterator i = activity.begin(); i != activity.end(); ++i) {
                    _activities.push_back(QString::fromStdString(*i));
                }
                _prev = activity;
                emit _q->numActivitiesChanged(activity.size());
            }
        }

        return false;
    }

    ActivityMonitorToolQtQml::Index::Index(ActivityMonitorTool* handler)
        : osgGA::GUIEventHandlerQtQml::Index(handler)

    {
    }
    void ActivityMonitorToolQtQml::Index::classBegin()
    {
    }

    void ActivityMonitorToolQtQml::Index::componentComplete()
    {
        if (!o(this)) {
            ActivityMonitorTool* handler = new ActivityMonitorTool(q(this));
            setO(handler);
        }
        osgGA::GUIEventHandlerQtQml::Index::componentComplete();
    }

    ActivityMonitorToolQtQml::ActivityMonitorToolQtQml(QObject* parent)
        : osgGA::GUIEventHandlerQtQml(parent)
    {
    }

    ActivityMonitorToolQtQml::ActivityMonitorToolQtQml(ActivityMonitorToolQtQml::Index* index, QObject* parent)
        : osgGA::GUIEventHandlerQtQml(index, parent)
    {
    }

    void ActivityMonitorToolQtQml::classBegin()
    {
        if (!i(this))
            setI(new Index);
        i(this)->setQ(this);
        osgGA::GUIEventHandlerQtQml::classBegin();
    }

    ActivityMonitorTool* ActivityMonitorToolQtQml::activityMonitorTool()
    {
        return o(this);
    }

    ActivityMonitorToolQtQml* ActivityMonitorToolQtQml::fromActivityMonitorTool(ActivityMonitorTool* handler, QObject* parent)
    {
        if (!handler)
            return 0;

        if (osgQtQml::Index* index = osgQtQml::Index::checkIndex(handler)) {
            return static_cast<ActivityMonitorToolQtQml*>(index->qtObject());
        }

        return new ActivityMonitorToolQtQml(new Index(handler), parent);
    }

    int ActivityMonitorToolQtQml::getNumActivities()
    {
        return o(this)->getActivities().size();
    }

    QString ActivityMonitorToolQtQml::getActivityAt(int index)
    {
        return o(this)->getActivities().at(index);
    }

    QStringList ActivityMonitorToolQtQml::activities()
    {
        //        return QQmlListProperty<QString>(this, (void*)0,
        //            (QQmlListProperty<QString>::CountFunction)ActivityMonitorToolQtQml::activitiesCount,
        //            (QQmlListProperty<QString>::AtFunction)ActivityMonitorToolQtQml::activitiesAt);
        return o(this)->getActivities();
    }

    //    int ActivityMonitorToolQtQml::activitiesCount(QQmlListProperty<QString>* list)
    //    {
    //        return static_cast<ActivityMonitorToolQtQml*>(list->object)->getNumActivities();
    //    }

    //    QString ActivityMonitorToolQtQml::activitiesAt(QQmlListProperty<QString>* list, int index)
    //    {
    //        return static_cast<ActivityMonitorToolQtQml*>(list->object)->getActivityAt(index);
    //    }
}
}
