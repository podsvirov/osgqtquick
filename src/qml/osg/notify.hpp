#ifndef _OSG_NOTIFY_QTQML_
#define _OSG_NOTIFY_QTQML_ 1

#include <osg/ObjectQtQml>

namespace osg {

class Notify;

class OSGQTQML_EXPORT NotifyQtQml : public osgQtQml::Object
{
  Q_OBJECT

  Q_PROPERTY(NotifyLevel notifyLevel READ getNotifyLevel WRITE setNotifyLevel NOTIFY notifyLevelChanged)

  Q_ENUMS(NotifyLevel)

public:
  enum NotifyLevel {
    ALWAYS=0,
    FATAL=1,
    WARN=2,
    NOTICE=3,
    INFO=4,
    DEBUG_INFO=5,
    DEBUG_FP=6
  };

  class Index;

  NotifyQtQml(QObject *parent = 0);
  NotifyQtQml(Index *index, QObject *parent = 0);

  virtual ~NotifyQtQml();

  void classBegin();

  Q_INVOKABLE NotifyLevel getNotifyLevel() const;
  Q_INVOKABLE void setNotifyLevel(const NotifyLevel level);

Q_SIGNALS:
  void notifyLevelChanged(const NotifyLevel level) const;

  void notify(const QString& message) const;
};

}

#endif // _OSG_NOTIFY_QTQML_
