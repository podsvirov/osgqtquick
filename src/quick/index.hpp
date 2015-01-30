#ifndef _OSGQTQUICK_INDEX_
#define _OSGQTQUICK_INDEX_ 1

#include <osgQtQuick/Export>

#include <osgQtQml/Index>

#include <QQuickItem>

namespace osgQtQuick {

class Object;

class OSGQTQUICK_EXPORT Index : public osgQtQml::Index
{
public:
    Index(osg::Object *object = 0);
    ~Index();

    void classBegin();

protected:
    QQuickItem *qthis;

private:
    friend class Object;
};

} // namespace osgQtQuick

#endif // _OSGQTQUICK_INDEX_
