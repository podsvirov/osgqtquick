#include "notify.hpp"
#include "notifyindex.hpp"

#include <osgQtQml/Index>

#include <osg/Notify>

#include <QLoggingCategory>

namespace osg {

/* --------------------------------------------- class NotifyHandlerQtQml --- */

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

/* ---------------------------------------------------------- class Index --- */

NotifyQtQml::Index::Index(NotifyHandler *o) :
    osgQtQml::Index(o)
{
}

void NotifyQtQml::Index::classBegin()
{
    if(!o(this) && q(this)) {
        setO(new NotifyHandlerQtQml(q(this)));
        osg::setNotifyLevel(osg::WARN);
        osg::setNotifyHandler(o(this));
    }

    osgQtQml::Index::classBegin();
}

NotifyQtQml::NotifyQtQml(QObject *parent) :
  osgQtQml::Object(parent)
{
}

NotifyQtQml::NotifyQtQml(NotifyQtQml::Index *index, QObject *parent) :
  osgQtQml::Object(index, parent)
{
}

NotifyQtQml::~NotifyQtQml()
{
    osg::setNotifyHandler(NULL);
}

void NotifyQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    osgQtQml::Object::classBegin();
}

NotifyQtQml::NotifyLevel NotifyQtQml::getNotifyLevel() const
{
    return static_cast<NotifyQtQml::NotifyLevel>(osg::getNotifyLevel());
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
