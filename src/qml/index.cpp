#include "index.hpp"

#include <QDebug>

namespace osgQtQml {

Storage Index::storage = Storage();

Index::Index(osg::Object *o) :
    o_ptr(o),
    q_ptr(0)
{
}

Index::~Index()
{
}

Index *Index::fromObject(osg::Object *o)
{
    std::map<osg::Object*, Index*>::iterator it = storage.osgIndexs.find(o);

    if (it != storage.osgIndexs.end()) return it->second;

    for(std::set<osgMakeIndex>::iterator it = storage.osgMakers.begin();
        it != storage.osgMakers.end(); ++ it)
    {
        if(Index *r = (*it)(o)) return r;
    }

    return 0;
}

Index *Index::fromObject(QObject *o)
{
    std::map<QObject*, Index*>::iterator it = storage.qtIndexs.find(o);

    if (it != storage.qtIndexs.end()) return it->second;

    for(std::set<qtMakeIndex>::iterator it = storage.qtMakers.begin();
        it != storage.qtMakers.end(); ++ it)
    {
        if(Index *r = (*it)(o)) return r;
    }

    return 0;
}

bool Index::insertMake(osgMakeIndex make)
{
    if (storage.osgMakers.find(make) != storage.osgMakers.end())
    {
        return false;
    }

    storage.osgMakers.insert(make);

    return true;
}

bool Index::eraseMake(osgMakeIndex make)
{
    std::set<osgMakeIndex>::iterator it = storage.osgMakers.find(make);

    if (it == storage.osgMakers.end())
    {
        return false;
    }

    storage.osgMakers.erase(it);

    return true;
}

bool Index::insertMake(qtMakeIndex make)
{
    if (storage.qtMakers.find(make) != storage.qtMakers.end())
    {
        return false;
    }

    make(0);

    storage.qtMakers.insert(make);

    return true;
}

bool Index::eraseMake(qtMakeIndex make)
{
    std::set<qtMakeIndex>::iterator it = storage.qtMakers.find(make);

    if (it == storage.qtMakers.end())
    {
        return false;
    }

    storage.qtMakers.erase(it);

    return true;
}

}
