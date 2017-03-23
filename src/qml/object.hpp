#ifndef _OSGQTQML_OBJECT_
#define _OSGQTQML_OBJECT_ 1

#include <osgQtQml/Export>
#include <QtQml/QQmlParserStatus>

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
  Object(Index *_i_ptr, QObject *parent = 0);

  template<typename T>
  typename T::Index* i(T *p);

  template<typename T>
  const typename T::Index* i(const T *p) const;

  template<typename T>
  typename T::Index::OType* o(T *p);

  template<typename T>
  const typename T::Index::OType* o(const T *p) const;

  void setI(Index *i);

  Index *_i_ptr;
  bool _is_begin;
  bool _is_complete;
};

inline bool Object::isBegin() const
{
  return _is_begin;
}

inline bool Object::isComplete() const
{
    return _is_complete;
}

inline void Object::setI(Index *i)
{
    _i_ptr = i;
}

template<typename T>
inline typename T::Index* Object::i(T *p)
{
    return static_cast<typename T::Index*>(p->_i_ptr);
}

template<typename T>
inline const typename T::Index* Object::i(const T *p) const
{
    return static_cast<const typename T::Index*>(p->_i_ptr);
}

template<typename T>
inline typename T::Index::OType* Object::o(T *p)
{
    return static_cast<typename T::Index::OType*>(p->_i_ptr->o_ptr.get());
}

template<typename T>
inline const typename T::Index::OType* Object::o(const T *p) const
{
    return static_cast<const typename T::Index::OType*>(p->_i_ptr->o_ptr.get());
}


}

#endif // _OSGQTQML_OBJECT_
