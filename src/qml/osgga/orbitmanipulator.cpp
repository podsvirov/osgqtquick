#include "orbitmanipulator.hpp"
#include "orbitmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/OrbitManipulator>

#include <QDebug>

/*!
   \qmltype OrbitManipulator
   \inherits StandardManipulator
   \inqmlmodule osgGA
   \brief Manipulator based on focal center, distance from the center,
   and orientation of distance vector to the eye
 */

namespace osgGA {

OrbitManipulatorQtQml::Index::Index(OrbitManipulator *manipulator) :
    StandardManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void OrbitManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new OrbitManipulator();
    StandardManipulatorQtQml::Index::othis = othis;
    StandardManipulatorQtQml::Index::qthis = qthis;

    StandardManipulatorQtQml::Index::classBegin();
}

OrbitManipulatorQtQml::OrbitManipulatorQtQml(QObject *parent) :
  StandardManipulatorQtQml(parent)
{
}

OrbitManipulatorQtQml::OrbitManipulatorQtQml(OrbitManipulatorQtQml::Index *index, QObject *parent) :
  StandardManipulatorQtQml(index, parent)
{
}

void OrbitManipulatorQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    StandardManipulatorQtQml::classBegin();
}

OrbitManipulator *OrbitManipulatorQtQml::orbitManipulator()
{
    return static_cast<Index*>(i)->othis;
}

OrbitManipulatorQtQml *OrbitManipulatorQtQml::fromOrbitManipulator(OrbitManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new OrbitManipulatorQtQml(new Index(trackballManipulator), parent);
}

}
