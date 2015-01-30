#ifndef _OSGQTQUICK_OBJECT_
#define _OSGQTQUICK_OBJECT_ 1

#include <osgQtQuick/Export>
#include <QQuickItem>

namespace osgQtQuick {

class Index;

class OSGQTQUICK_EXPORT Object : public QQuickItem
{
  Q_OBJECT

public:
  Object(QQuickItem *parent = 0);
  ~Object();

  void classBegin();
  void componentComplete();

  Index* index();

protected:
  Object(Index *i, QQuickItem *parent = 0);
  Index *i;
};

}

#endif // _OSGQTQUICK_OBJECT_
