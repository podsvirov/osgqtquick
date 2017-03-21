#include "firstpersonmanipulator.hpp"
#include "firstpersonmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/FirstPersonManipulator>

#include <QtCore/QDebug>

/*!
   \qmltype FirstPersonManipulator
   \inherits StandardManipulator
   \inqmlmodule osgGA
   \brief Control based on position and orientation
 */

namespace osgGA {

FirstPersonManipulatorQtQml::Index::Index(FirstPersonManipulator *manipulator) :
    StandardManipulatorQtQml::Index(manipulator)
{
}

void FirstPersonManipulatorQtQml::Index::classBegin()
{
    if(!o(this)) setO(new FirstPersonManipulator);

    StandardManipulatorQtQml::Index::classBegin();
}

FirstPersonManipulatorQtQml::FirstPersonManipulatorQtQml(QObject *parent) :
  StandardManipulatorQtQml(parent)
{
}

FirstPersonManipulatorQtQml::FirstPersonManipulatorQtQml(FirstPersonManipulatorQtQml::Index *index, QObject *parent) :
  StandardManipulatorQtQml(index, parent)
{
}

void FirstPersonManipulatorQtQml::classBegin()
{
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    StandardManipulatorQtQml::classBegin();
}

FirstPersonManipulator *FirstPersonManipulatorQtQml::firstPersonManipulator()
{
    return o(this);
}

FirstPersonManipulatorQtQml *FirstPersonManipulatorQtQml::fromFirstPersonManipulator(FirstPersonManipulator *manipulator, QObject *parent)
{
    if(!manipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(manipulator))
    {
        return static_cast<FirstPersonManipulatorQtQml*>(index->qtObject());
    }

    FirstPersonManipulatorQtQml *result = new FirstPersonManipulatorQtQml(new Index(manipulator), parent);
    result->classBegin();
    return result;
}

}
