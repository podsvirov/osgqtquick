#ifndef _OSGQTQUICK_OBJECT_
#define _OSGQTQUICK_OBJECT_ 1

#include <osgQtQuick/Export>
#include <QQuickItem>

namespace osgQtQml {

class Index;

}

namespace osgQtQuick {

class OSGQTQUICK_EXPORT Object : public QQuickItem
{
  Q_OBJECT

public:
  Object(QQuickItem *parent = 0);
  ~Object();

  void classBegin();
  void componentComplete();

  osgQtQml::Index* index();

protected:
  Object(osgQtQml::Index *i, QQuickItem *parent = 0);
  osgQtQml::Index *i;
};

}

#endif // _OSGQTQUICK_OBJECT_
