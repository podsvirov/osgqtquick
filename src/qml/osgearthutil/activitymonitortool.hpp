#ifndef _OSGEARTHUTIL_ACTIVITY_MONITOR_TOOL_QTQML_
#define _OSGEARTHUTIL_ACTIVITY_MONITOR_TOOL_QTQML_ 1

#include <QQmlListProperty>
#include <QStringList>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventHandlerQtQml>

namespace osgEarth {
namespace Util {
    class ActivityMonitorToolQtQml;
    class ActivityMonitorTool : public osgGA::GUIEventHandler {

    public: // GUIEventHandler
        ActivityMonitorTool(ActivityMonitorToolQtQml* q);
        bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

        QStringList& getActivities() { return _activities; }

    protected:
        ActivityMonitorToolQtQml* _q;
        std::set<std::string> _prev;
        QStringList _activities;
    };

    class OSGQTQML_EXPORT ActivityMonitorToolQtQml : public osgGA::GUIEventHandlerQtQml {
        Q_OBJECT
    public:
        class Index;
        ActivityMonitorToolQtQml(QObject* parent = 0);
        ActivityMonitorToolQtQml(Index* index, QObject* parent = 0);

        Q_PROPERTY(int numActivities READ getNumActivities NOTIFY numActivitiesChanged)
        Q_PROPERTY(QStringList activities READ activities NOTIFY numActivitiesChanged)

        virtual void classBegin();

        ActivityMonitorTool* activityMonitorTool();
        static ActivityMonitorToolQtQml* fromActivityMonitorTool(ActivityMonitorTool* handler, QObject* parent = 0);

        Q_INVOKABLE int getNumActivities();
        Q_INVOKABLE QString getActivityAt(int index);
        QStringList activities();

    signals:
        void numActivitiesChanged(int num);

        //    protected:
        //        static int activitiesCount(QQmlListProperty<QString>* list);
        //        static QString activitiesAt(QQmlListProperty<QString>* list, int index);
    };
}
}

#endif
