#include "index.hpp"

#include <QtCore/QDebug>

namespace osgQtQml {

Storage Index::storage = Storage();

Index::Index(osg::Referenced *o) :
    is_begin(false), is_complete(false),
    o_ptr(o),
    q_ptr(0)
{
}

Index::~Index()
{
    storage.qtIndexes.erase(q(this));
    storage.osgIndexes.erase(o(this));

    if(storage.osgIndexes.empty() && storage.qtIndexes.empty())
    {
        qDebug() << "[osgQtQuick] Index cleared";
    }
}



void Index::classBegin()
{
    is_begin = true;
}

void Index::componentComplete()
{
    if(!o_ptr.get() || !q_ptr.data())
    {
        qDebug() << "[osgQtQuick] Component initialization error";
    }

    storage.qtIndexes.insert(std::pair<QObject*, Index*>(q_ptr.data(), this));
    storage.osgIndexes.insert(std::pair<osg::Referenced*, Index*>(o_ptr.get(), this));

    is_complete = true;
}

Index *Index::checkIndex(osg::Referenced *o)
{
    std::map<osg::Referenced*, Index*>::iterator it = storage.osgIndexes.find(o);

    if (it != storage.osgIndexes.end()) return it->second;

    return 0;
}

Index *Index::checkIndex(QObject *o)
{
    std::map<QObject*, Index*>::iterator it = storage.qtIndexes.find(o);

    if (it != storage.qtIndexes.end()) return it->second;

    return 0;
}

Index *Index::fromObject(osg::Object *o)
{
    std::map<osg::Referenced*, Index*>::iterator it = storage.osgIndexes.find(o);

    if (it != storage.osgIndexes.end()) return it->second;

    for(std::set<osgMakeIndex>::iterator it = storage.osgMakers.begin();
        it != storage.osgMakers.end(); ++ it)
    {
        if(Index *r = (*it)(o)) return r;
    }

    return 0;
}

Index *Index::fromObject(QObject *o)
{
    std::map<QObject*, Index*>::iterator it = storage.qtIndexes.find(o);

    if (it != storage.qtIndexes.end()) return it->second;

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
