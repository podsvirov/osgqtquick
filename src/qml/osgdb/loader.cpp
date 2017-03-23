#include "loader.hpp"
#include "loaderindex.hpp"

#include <osgQtQml/Index>

#include <osgDB/ReadFile>

#include <QtCore/QDebug>

/*!
   \qmltype Loader
   \inherits osg::Group
   \inqmlmodule osgDB
   \brief Loader of nodes

   The Loader item allows dynamically loading an \l {osg::Node}{Node}-based subtree from a URL
 */


namespace osgDB {

LoaderQtQml::Index::Index(osg::Group *group) :
    GroupQtQml::Index(group),
    status(LoaderQtQml::Null)
{
}

LoaderQtQml::Index::~Index()
{
}

void LoaderQtQml::Index::classBegin()
{
    if(!o(this)) setO(new osg::Group);

    GroupQtQml::Index::classBegin();
}

void LoaderQtQml::Index::setUrl(const QUrl &url)
{
    if(this->url == url) return;

    this->url = url;

    emit q(this)->sourceChanged(this->url);

    Loader *loader = new Loader(this->url);
    connect(loader, SIGNAL(loaded(const QUrl&, osg::Node*)), q(this), SLOT(nodeLoadingDone(const QUrl &, osg::Node*)));
    connect(loader, SIGNAL(finished()), loader, SLOT(deleteLater()));
    loader->start();

    status = LoaderQtQml::Loading;

    emit q(this)->statusChanged(status);
}

osg::NodeQtQml *LoaderQtQml::Index::getNode()
{
    return osg::NodeQtQml::fromNode(node.get());
}

void LoaderQtQml::Index::acceptNode(const QUrl &url, osg::Node *node)
{
    if (this->url != url) return;

    if(this->node.valid())
    {
        this->status = LoaderQtQml::Error;
        o(this)->removeChild(this->node.get());
    }

    if(node)
    {
        this->status = LoaderQtQml::Ready;
        o(this)->addChild(node);
    }

    this->node = node;

    emit q(this)->nodeChanged(getNode());

    emit q(this)->statusChanged(this->status);
}

LoaderQtQml::LoaderQtQml(QObject *parent) :
  GroupQtQml(parent)
{
}

LoaderQtQml::LoaderQtQml(LoaderQtQml::Index *index, QObject *parent) :
  GroupQtQml(index, parent)
{
}

void LoaderQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    GroupQtQml::classBegin();
}

/*!
   \qmlproperty url osgDB::Loader::source

   This property holds the URL of the \l {osg::Node}{Node} to instantiate.
 */

QUrl LoaderQtQml::getSource()
{
    return i(this)->url;
}

void LoaderQtQml::setSource(const QUrl &url)
{
    i(this)->setUrl(url);
}

/*!
   \qmlproperty osg::Node osgDB::Loader::node

   Loaded \l {osg::Node}{node}.
 */

osg::NodeQtQml *LoaderQtQml::getNode()
{
    return i(this)->getNode();
}

/*!
   \qmlproperty enumeration osgDB::Loader::status

   This property holds the status of Node loading.  It can be one of:
   \list
   \li Loader.Null - the node source has not been set
   \li Loader.Loading - the node source is currently being loaded
   \li Loader.Ready - the node source has been loaded
   \li Loader.Error - an error occurred while loading the node source
   \endlist
 */

LoaderQtQml::Status LoaderQtQml::getStatus()
{
    return i(this)->status;
}

LoaderQtQml *LoaderQtQml::fromGroup(osg::Group *group, QObject *parent)
{
    if(!group) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(group))
    {
        return static_cast<LoaderQtQml*>(index->qtObject());
    }

    LoaderQtQml *result = new LoaderQtQml(new Index(group), parent);
    result->classBegin();
    return result;
}

void LoaderQtQml::nodeLoadingDone(const QUrl &url, osg::Node *node)
{
    i(this)->acceptNode(url, node);
}

}
