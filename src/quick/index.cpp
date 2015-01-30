#include "index.hpp"

namespace osgQtQuick {

Index::Index(osg::Object *object) :
    osgQtQml::Index(object),
    qthis(0)
{
}

Index::~Index()
{

}

void Index::classBegin()
{
    osgQtQml::Index::qthis = qthis;

    osgQtQml::Index::classBegin();
}

} // namespace osgQtQuick

