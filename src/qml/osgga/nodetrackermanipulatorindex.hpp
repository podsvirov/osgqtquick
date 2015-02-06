#ifndef _OSGGA_NODETRACKERMANIPULATOR_QTQML_INDEX_
#define _OSGGA_NODETRACKERMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/NodeTrackerManipulatorQtQml>

#include <osgGA/OrbitManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT NodeTrackerManipulatorQtQml::Index : public OrbitManipulatorQtQml::Index
{
    friend class NodeTrackerManipulatorQtQml;

public:
    Index(NodeTrackerManipulator *o = 0);

    void classBegin();

    void setTrackNode(osg::NodeQtQml *node);

protected:
    NodeTrackerManipulator *othis;
    NodeTrackerManipulatorQtQml *qthis;
};

}

#endif // _OSGGA_NODETRACKERMANIPULATOR_QTQML_INDEX_
