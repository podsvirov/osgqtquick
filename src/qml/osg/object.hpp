#ifndef _OSG_OBJECT_QTQML_
#define _OSG_OBJECT_QTQML_ 1

#include <osgQtQml/Object>

namespace osg {

class Object;

class OSGQTQML_EXPORT ObjectQtQml : public osgQtQml::Object
{
  Q_OBJECT

public:
  class Index;

  ObjectQtQml(QObject *parent = 0);
  ObjectQtQml(Index *index, QObject *parent = 0);

  void classBegin();

  osg::Object* object();

  static ObjectQtQml* fromObject(osg::Object *object, QObject *parent = 0);
};

}

#endif // _OSG_OBJECT_QTQML_
