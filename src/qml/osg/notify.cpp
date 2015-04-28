#include "notify.hpp"
#include "notifyindex.hpp"

#include <osgQtQml/Index>

#include <osg/Node>

#include <QLoggingCategory>

namespace osg {

NotifyQtQml::Index::Index() :
    ObjectQtQml::Index(),
    qthis(0)
{
}

void NotifyQtQml::Index::classBegin()
{
    if(!othis) othis = new Node();
    osgQtQml::Index::othis = othis;
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

//-------------

class NotifyHandlerQtQml : public osg::NotifyHandler
{
public:
    NotifyHandlerQtQml(NotifyQtQml* notifyQtQml) : _notifyQtQml(notifyQtQml) {};

    void notify(osg::NotifySeverity severity, const char *message) {
        if(severity == osg::FATAL) {
            QLoggingCategory category("osgQtQuick");
            qCCritical(category, message);
        }
        if(_notifyQtQml) {
            const QString qMessage(message);
            emit _notifyQtQml->notify(qMessage);
        }
    }

protected:
    NotifyQtQml* _notifyQtQml;
};

//----------------------------------------------------------------------

NotifyQtQml::NotifyQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
    osg::setNotifyLevel(osg::WARN);
    osg::setNotifyHandler(new NotifyHandlerQtQml(this));
}

NotifyQtQml::NotifyQtQml(NotifyQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
    osg::setNotifyLevel(osg::WARN);
    osg::setNotifyHandler(new NotifyHandlerQtQml(this));
}

NotifyQtQml::~NotifyQtQml()
{
    osg::setNotifyHandler(NULL);
}

void NotifyQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    osgQtQml::Object::classBegin();
}

NotifyQtQml::NotifyLevel NotifyQtQml::getNotifyLevel() const
{
    return (NotifyQtQml::NotifyLevel)osg::getNotifyLevel();
}

void NotifyQtQml::setNotifyLevel(const NotifyQtQml::NotifyLevel level)
{
    if(getNotifyLevel() != level)
    {
        osg::setNotifyLevel((osg::NotifySeverity)level);
        osg::setNotifyHandler(new NotifyHandlerQtQml(this));
        emit notifyLevelChanged(level);
    }
}

}
