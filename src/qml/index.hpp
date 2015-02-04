#ifndef _OSGQTQML_INDEX_
#define _OSGQTQML_INDEX_ 1

#include <osgQtQml/Export>

#include <osg/Object>
#include <osg/Vec4>

#include <QObject>
#include <QPointer>
#include <QColor>

#include <list>
#include <set>

namespace osgQt {

inline osg::Vec4 swapColor(const QColor& color)
{
    return osg::Vec4(color.redF(),
                     color.greenF(),
                     color.blueF(),
                     color.alphaF());
}

inline QColor swapColor(const osg::Vec4& color)
{
    return QColor::fromRgbF(color.r(),
                            color.g(),
                            color.b(),
                            color.a());
}

}

namespace osgQtQuick {

class Object;

}

namespace osgQtQml {

class Index;
class Object;

typedef Index* (*qtMakeIndex) (QObject*);
typedef Index* (*osgMakeIndex)  (osg::Object*);

struct OSGQTQML_EXPORT Storage {
    std::set<qtMakeIndex> qtMakers;
    std::set<osgMakeIndex> osgMakers;
    std::map<QObject*, Index*> qtIndexes;
    std::map<osg::Object*, Index*> osgIndexes;
};

class OSGQTQML_EXPORT Index
{
public:
    Index(osg::Object *o_ptr = 0);
    virtual ~Index();

public: // methods
    QObject *qtObject();
    osg::Object *osgObject();

    bool isBegin() const;

    virtual void classBegin();

public: // static methods
    static Index *checkIndex(osg::Object *o_ptr);
    static Index *checkIndex(QObject *o_ptr);

    static Index *fromObject(osg::Object *o_ptr);
    static Index *fromObject(QObject *o_ptr);

    static bool insertMake(osgMakeIndex make);
    static bool eraseMake(osgMakeIndex make);

    static bool insertMake(qtMakeIndex make);
    static bool eraseMake(qtMakeIndex make);

protected:
    osg::Object *othis;
    QObject *qthis;

    void setQtObject(QObject *object);
    void setOSGObject(osg::Object *object);

private:
    friend class ::osgQtQml::Object;
    friend class ::osgQtQuick::Object;

    bool is_begin;

    osg::ref_ptr<osg::Object> o_ptr;
    QPointer<QObject> q_ptr;

    static Storage storage;
};

inline QObject *Index::qtObject()
{
    return q_ptr.data();
}

inline osg::Object *Index::osgObject()
{
    return o_ptr.get();
}

inline bool Index::isBegin() const
{
    return is_begin;
}

inline void Index::setQtObject(QObject *object)
{
    q_ptr = object;
}

inline void Index::setOSGObject(osg::Object *object)
{
    o_ptr = object;
}

}

#endif // _OSGQTQML_INDEX_
