#include "trackballmanipulator.hpp"
#include "trackballmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/TrackballManipulator>

#include <QtCore/QDebug>

/*!
   \qmltype TrackballManipulator
   \inherits OrbitManipulator
   \inqmlmodule osgGA
   \brief Trackball manipulator
 */

namespace osgGA {

TrackballManipulatorQtQml::Index::Index(TrackballManipulator *manipulator) :
    OrbitManipulatorQtQml::Index(manipulator)
{
}

void TrackballManipulatorQtQml::Index::classBegin()
{
    if(!o(this)) setO(new TrackballManipulator);

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
    if(!i(this)) setI(new Index);

    i(this)->setQ(this);

    OrbitManipulatorQtQml::classBegin();
}

TrackballManipulator *TrackballManipulatorQtQml::trackballManipulator()
{
    return o(this);
}

TrackballManipulatorQtQml *TrackballManipulatorQtQml::fromTrackballManipulator(TrackballManipulator *trackballManipulator, QObject *parent)
{
    if(!trackballManipulator) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(trackballManipulator))
    {
        return static_cast<TrackballManipulatorQtQml*>(index->qtObject());
    }

    TrackballManipulatorQtQml *result = new TrackballManipulatorQtQml(new Index(trackballManipulator), parent);
    result->classBegin();
    return result;
}

}
