#include "stateset.hpp"
#include "statesetindex.hpp"

#include <osgQtQml/Index>

#include <osg/StateSet>

namespace osg {

/*!
   \qmltype StateSet
   \inherits Object
   \inqmlmodule osg
   \brief Stores a set of modes and attributes which represent a set
   of OpenGL state
 */

StateSetQtQml::Index::Index(StateSet *StateSet) :
    ObjectQtQml::Index(StateSet)
{
}

void StateSetQtQml::Index::classBegin()
{
    if(!o(this)) setO(new StateSet);

    ObjectQtQml::Index::classBegin();
}

StateSetQtQml::StateSetQtQml(QObject *parent) :
  ObjectQtQml(parent)
{
}

StateSetQtQml::StateSetQtQml(StateSetQtQml::Index *index, QObject *parent) :
  ObjectQtQml(index, parent)
{
}

void StateSetQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    ObjectQtQml::classBegin();
}

/*!
   \qmlmethod void osg::StateSet::setGlobalDefaults()

   Set all the modes to on or off so that it defines a complete state
   typically used for a default global state.
 */

void StateSetQtQml::setGlobalDefaults()
{
    o(this)->setGlobalDefaults();
}

StateSet *StateSetQtQml::stateSet()
{
    return o(this);
}

StateSetQtQml *StateSetQtQml::fromStateSet(StateSet *stateSet, QObject *parent)
{
    if(!stateSet) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(stateSet))
    {
        return static_cast<StateSetQtQml*>(index->qtObject());
    }

    StateSetQtQml *result = new StateSetQtQml(new Index(stateSet), parent);
    result->classBegin();

    return result;
}

}
