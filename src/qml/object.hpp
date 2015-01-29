#ifndef _OSGQTQML_OBJECT_
#define _OSGQTQML_OBJECT_ 1

#include <osgQtQml/Export>
#include <QQmlParserStatus>

namespace osgQtQml {

class Index;

class OSGQTQML_EXPORT Object : public QObject, public QQmlParserStatus
{
  Q_OBJECT
  Q_INTERFACES(QQmlParserStatus)

public:
  Object(QObject *parent = 0);
  ~Object();

  void classBegin();
  void componentComplete();

  Index* index();

protected:
  Object(Index *i, QObject *parent = 0);
  Index *i;
};

}

#endif // _OSGQTQML_OBJECT_
