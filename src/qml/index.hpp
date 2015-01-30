#ifndef _OSGQTQML_INDEX_
#define _OSGQTQML_INDEX_ 1

#include <osgQtQml/Export>

#include <osg/Object>

#include <QObject>
#include <QPointer>

#include <list>
#include <set>

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
    std::map<QObject*, Index*> qtIndexs;
    std::map<osg::Object*, Index*> osgIndexs;
};

class OSGQTQML_EXPORT Index
{
public:
    Index(osg::Object *o_ptr = 0);
    virtual ~Index();

public: // methods
    QObject *qtObject();
    osg::Object *osgObject();

public: // static methods
    static Index *fromObject(osg::Object *o_ptr);
    static Index *fromObject(QObject *o_ptr);

    static bool insertMake(osgMakeIndex make);
    static bool eraseMake(osgMakeIndex make);

    static bool insertMake(qtMakeIndex make);
    static bool eraseMake(qtMakeIndex make);

private:
    bool registrate();

    friend class ::osgQtQml::Object;
    friend class ::osgQtQuick::Object;

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

}

#endif // _OSGQTQML_INDEX_
