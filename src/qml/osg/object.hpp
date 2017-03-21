#ifndef _OSG_OBJECT_QTQML_
#define _OSG_OBJECT_QTQML_ 1

#include <osgQtQml/Object>

namespace osg {

class Object;

class OSGQTQML_EXPORT ObjectQtQml : public osgQtQml::Object
{
  Q_OBJECT

  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
  class Index;

  ObjectQtQml(QObject *parent = 0);
  ObjectQtQml(Index *index, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE QString getName() const;
  Q_INVOKABLE void setName(const QString &name);

  osg::Object* object();

  static ObjectQtQml* fromObject(osg::Object *object, QObject *parent = 0);

Q_SIGNALS:
  void nameChanged(QString name) const;
};

}

#endif // _OSG_OBJECT_QTQML_
