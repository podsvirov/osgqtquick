#ifndef _OSGQTQUICK_INDEX_
#define _OSGQTQUICK_INDEX_ 1

#include <osgQtQuick/Export>

#include <osgQtQml/Index>

#include <osg/View>

#include <QQuickItem>
#include <QQuickWindow>
#include <QKeyEvent>

#include <map>

namespace osgQt {

OSGQTQUICK_EXPORT extern std::map<unsigned int, int> keyMap;

inline int swapKey(QKeyEvent *event)
{
    std::map<unsigned int, int>::iterator it =
            keyMap.find(event->key());
    return it == keyMap.end() ?
                static_cast<int>(*(event->text().toLatin1().data())) :
                it->second;
}

}

namespace osgQtQuick {

class Object;
class Window;

struct Storage
{
    std::map<QQuickWindow*, Window*> windows;
};

class OSGQTQUICK_EXPORT Index : public osgQtQml::Index
{
public:
    typedef osg::View OType;
    typedef Object QType;

public:
    Index(osg::Object *object = 0);
    ~Index();

    void classBegin();

protected:
    template<typename T>
    typename T::OType* o(T *p);

    void setO(osg::View *o);

    osg::View *o_ptr;

private:
    friend class Object;
    friend class Window;

    static Storage storage;
};

template<typename T>
inline typename T::OType* Index::o(T *p)
{
    return static_cast<typename T::OType*>(p->o_ptr);
}

inline void Index::setO(osg::View *o)
{
    o_ptr = o;
    osgQtQml::Index::setO(o);
}

} // namespace osgQtQuick

#endif // _OSGQTQUICK_INDEX_
