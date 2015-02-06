#ifndef _OSG_GEODE_QTQML_
#define _OSG_GEODE_QTQML_ 1

#include <osg/NodeQtQml>
#include <osg/DrawableQtQml>

namespace osg {

class Geode;

class OSGQTQML_EXPORT GeodeQtQml : public NodeQtQml
{
  Q_OBJECT

  Q_PROPERTY(int numDrawables READ getNumDrawables NOTIFY numDrawablesChanged)

public:
  class Index;

  GeodeQtQml(QObject *parent = 0);
  GeodeQtQml(Index *, QObject *parent = 0);

  void classBegin();

  Q_INVOKABLE bool addDrawable(DrawableQtQml *drawable);
  Q_INVOKABLE bool removeDrawable(DrawableQtQml *drawable);

  Q_INVOKABLE int getNumDrawables() const;

  Geode* geode();

  static GeodeQtQml* fromGeode(Geode *geode, QObject *parent = 0);

signals:
  void numDrawablesChanged(int num);
};

}

#endif // _OSG_GEODE_QTQML_
