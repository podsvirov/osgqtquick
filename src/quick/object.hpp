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

  template<typename T, typename I = typename T::Index>
  I* i(T *p);

  template<typename T, typename O = typename T::Index::OType>
  O* o(T *p);

  void setI(Index *i);

  Index *_i_ptr;
};

template<typename T, typename I>
inline I* Object::i(T *p)
{
    return static_cast<I*>(p->_i_ptr);
}

template<typename T, typename O>
inline O* Object::o(T *p)
{
    return static_cast<O*>(i(p)->othis);
}

inline void Object::setI(Index *i)
{
    _i_ptr = i;
}

}

#endif // _OSGQTQUICK_OBJECT_
