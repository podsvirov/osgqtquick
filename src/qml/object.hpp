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

  bool isBegin() const;
  bool isComplete() const;

protected:
  Object(Index *i, QObject *parent = 0);
  Index *i;
  bool _isBegin;
  bool _isComplete;
};

inline bool Object::isBegin() const
{
  return _isBegin;
}

inline bool Object::isComplete() const
{
  return _isComplete;
}

}

#endif // _OSGQTQML_OBJECT_
