#include "firstpersonmanipulator.hpp"
#include "firstpersonmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/FirstPersonManipulator>

#include <QDebug>

namespace osgGA {

FirstPersonManipulatorQtQml::Index::Index(FirstPersonManipulator *manipulator) :
    StandardManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void FirstPersonManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new FirstPersonManipulator();
    StandardManipulatorQtQml::Index::othis = othis;
    StandardManipulatorQtQml::Index::qthis = qthis;

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
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    StandardManipulatorQtQml::classBegin();
}

FirstPersonManipulator *FirstPersonManipulatorQtQml::firstPersonManipulator()
{
    return static_cast<Index*>(i)->othis;
}

FirstPersonManipulatorQtQml *FirstPersonManipulatorQtQml::fromFirstPersonManipulator(FirstPersonManipulator *manipulator, QObject *parent)
{
    if(!manipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(manipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new FirstPersonManipulatorQtQml(new Index(manipulator), parent);
}

}
