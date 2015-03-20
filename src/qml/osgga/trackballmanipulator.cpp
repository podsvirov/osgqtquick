#include "trackballmanipulator.hpp"
#include "trackballmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/TrackballManipulator>

#include <QDebug>

/*!
   \qmltype TrackballManipulator
   \inherits OrbitManipulator
   \inqmlmodule osgGA
   \brief Trackball manipulator
 */

namespace osgGA {

TrackballManipulatorQtQml::Index::Index(TrackballManipulator *manipulator) :
    OrbitManipulatorQtQml::Index(manipulator),
    qthis(0)
{
    othis = manipulator;
}

void TrackballManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new TrackballManipulator();
    OrbitManipulatorQtQml::Index::othis = othis;
    OrbitManipulatorQtQml::Index::qthis = qthis;

    OrbitManipulatorQtQml::Index::classBegin();
}

TrackballManipulatorQtQml::TrackballManipulatorQtQml(QObject *parent) :
  OrbitManipulatorQtQml(parent)
{
}

TrackballManipulatorQtQml::TrackballManipulatorQtQml(TrackballManipulatorQtQml::Index *index, QObject *parent) :
  OrbitManipulatorQtQml(index, parent)
{
}

void TrackballManipulatorQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    OrbitManipulatorQtQml::classBegin();
}

TrackballManipulator *TrackballManipulatorQtQml::trackballManipulator()
{
    return static_cast<Index*>(i)->othis;
}

TrackballManipulatorQtQml *TrackballManipulatorQtQml::fromTrackballManipulator(TrackballManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<Index*>(index)->qthis;
    }

    return new TrackballManipulatorQtQml(new Index(trackballManipulator), parent);
}

}
