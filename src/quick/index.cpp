#include "index.hpp"

namespace osgQtQuick {

Storage Index::storage = Storage();

Index::Index(osg::Object *object) :
    osgQtQml::Index(object),
    o_ptr(0)
{
}

Index::~Index()
{

}

void Index::classBegin()
{
    osgQtQml::Index::classBegin();
}

} // namespace osgQtQuick

