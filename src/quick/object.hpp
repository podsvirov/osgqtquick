#ifndef _OSGQTQUICK_OBJECT_
#define _OSGQTQUICK_OBJECT_ 1

#include <osgQtQuick/Export>
#include <QtQuick/QQuickItem>

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

  template<typename T>
  typename T::Index* i(T *p);

  template<typename T>
  typename T::Index::OType* o(T *p);

  void setI(Index *i);

  Index *_i_ptr;
};

template<typename T>
inline typename T::Index* Object::i(T *p)
{
    return static_cast<typename T::Index*>(p->_i_ptr);
}

template<typename T>
inline typename T::Index::OType* Object::o(T *p)
{
    return static_cast<typename T::Index::OType*>(i(p)->o_ptr);
}

inline void Object::setI(Index *i)
{
    _i_ptr = i;
}

}

#endif // _OSGQTQUICK_OBJECT_
