#include "loader.hpp"
#include "loaderindex.hpp"

#include <osgQtQml/Index>

#include <osgDB/ReadFile>

#include <QDebug>

namespace osgDB {

LoaderQtQml::Index::Index(osg::Group *group) :
    GroupQtQml::Index(group),
    qthis(0)
{
    othis = group;
}

LoaderQtQml::Index::~Index()
{
}

void LoaderQtQml::Index::classBegin()
{
    if(!othis) othis = new osg::Group();
    GroupQtQml::Index::othis = othis;
    GroupQtQml::Index::qthis = qthis;

    GroupQtQml::Index::classBegin();
}

void LoaderQtQml::Index::setUrl(const QUrl &url)
{
    if(this->url == url) return;

    this->url = url;

    Loader *loader = new Loader(this->url);
    connect(loader, SIGNAL(loaded(const QUrl&, osg::Node*)), qthis, SLOT(nodeLoadingDone(const QUrl &, osg::Node*)));
    connect(loader, SIGNAL(finished()), loader, SLOT(deleteLater()));
    loader->start();

    emit qthis->sourceChanged(this->url);
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
        othis->removeChild(this->node.get());
    }

    if(node)
    {
        othis->addChild(node);
    }

    this->node = node;
    emit qthis->nodeChanged(getNode());
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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    GroupQtQml::classBegin();
}

void LoaderQtQml::setSource(const QUrl &url)
{
    static_cast<Index*>(i)->setUrl(url);
}

QUrl LoaderQtQml::getSource()
{
    return static_cast<Index*>(i)->url;
}

osg::NodeQtQml *LoaderQtQml::getNode()
{
    return static_cast<Index*>(i)->getNode();
}

LoaderQtQml *LoaderQtQml::fromGroup(osg::Group *group, QObject *parent)
{
    if(!group) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(group))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new LoaderQtQml(new Index(group), parent);
}

void LoaderQtQml::nodeLoadingDone(const QUrl &url, osg::Node *node)
{
    static_cast<Index*>(i)->acceptNode(url, node);
}

}
