#include "trackballmanipulator.hpp"
#include "trackballmanipulatorindex.hpp"

#include <osgQtQml/Index>

#include <osgGA/TrackballManipulator>

#include <QDebug>

namespace osgGA {

TrackballManipulatorQtQml::Index::Index(TrackballManipulator *trackballManipulator) :
    CameraManipulatorQtQml::Index(),
    qthis(0)
{
    othis = trackballManipulator;
}

void TrackballManipulatorQtQml::Index::classBegin()
{
    if(!othis) othis = new TrackballManipulator();
    CameraManipulatorQtQml::Index::othis = othis;
    CameraManipulatorQtQml::Index::qthis = qthis;

    CameraManipulatorQtQml::Index::classBegin();
}

TrackballManipulatorQtQml::TrackballManipulatorQtQml(QObject *parent) :
  CameraManipulatorQtQml(parent)
{
}

TrackballManipulatorQtQml::TrackballManipulatorQtQml(TrackballManipulatorQtQml::Index *index, QObject *parent) :
  CameraManipulatorQtQml(index, parent)
{
}

void TrackballManipulatorQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    CameraManipulatorQtQml::classBegin();
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
