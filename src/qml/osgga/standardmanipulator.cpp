#include "standardmanipulator.hpp"
#include "standardmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/StandardManipulator>

#include <QDebug>

namespace osgGA {

StandardManipulatorQtQml::Index::Index(StandardManipulator *manipulator) :
    CameraManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void StandardManipulatorQtQml::Index::classBegin()
{
    CameraManipulatorQtQml::Index::othis = othis;
    CameraManipulatorQtQml::Index::qthis = qthis;

    CameraManipulatorQtQml::Index::classBegin();
}

StandardManipulatorQtQml::StandardManipulatorQtQml(QObject *parent) :
  CameraManipulatorQtQml(parent)
{
}

StandardManipulatorQtQml::StandardManipulatorQtQml(StandardManipulatorQtQml::Index *index, QObject *parent) :
  CameraManipulatorQtQml(index, parent)
{
}

void StandardManipulatorQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    CameraManipulatorQtQml::classBegin();
}

StandardManipulator *StandardManipulatorQtQml::standardManipulator()
{
    return static_cast<Index*>(i)->othis;
}

StandardManipulatorQtQml *StandardManipulatorQtQml::fromStandardManipulator(StandardManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new StandardManipulatorQtQml(new Index(trackballManipulator), parent);
}

}
