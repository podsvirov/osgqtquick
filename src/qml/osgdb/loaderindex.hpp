#ifndef _OSGDB_LOADER_QTQML_INDEX_
#define _OSGDB_LOADER_QTQML_INDEX_ 1

#include <osgDB/LoaderQtQml>

#include <osg/GroupQtQmlIndex>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

#include <QThread>

#include <QDebug>
#include <QFileInfo>

#include <cstdlib>
#include <QDir>

namespace osgDB {

class OSGQTQML_EXPORT LoaderQtQml::Index : public GroupQtQml::Index
{
    friend class LoaderQtQml;

    class Loader;

public:
    Index(osg::Group *o = 0);
    ~Index();

    void classBegin();

    void setUrl(const QUrl &url);

    osg::NodeQtQml* getNode();

protected:
    void acceptNode(const QUrl &url, osg::Node *node);

    osg::Group *othis;
    LoaderQtQml *qthis;

    QUrl url;
    osg::ref_ptr<osg::Node> node;
};

class LoaderQtQml::Index::Loader : public QThread
{
    Q_OBJECT

public:
    Loader(const QUrl &url) : url(url) {
    }

    void run() {
        if(url.isLocalFile()) {
            QFileInfo info(url.toLocalFile());            
            if(info.exists())
            {
                node = readNodeFile(info.filePath().toStdString());
            }
            else
            {
                std::string file = osgDB::findDataFile(url.fileName().toStdString());
                if(!file.empty())
                {
                    node = readNodeFile(file);
                }
            }
        }
        else { // no local file
            QString qfile = url.toString().remove("file:///");
            if(!qfile.isEmpty())
            {
                node = readNodeFile(qfile.toStdString());
            }
        }

        emit loaded(url, node.get());
    }

signals:
    void loaded(const QUrl& url, osg::Node *node);

private:
    QUrl url;
    osg::ref_ptr<osg::Node> node;
};

}

#endif // _OSGDB_LOADER_QTQML_INDEX_
