#ifndef _OSGGA_STANDARDMANIPULATOR_QTQML_INDEX_
#define _OSGGA_STANDARDMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/StandardManipulatorQtQml>

#include <osgGA/CameraManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT StandardManipulatorQtQml::Index : public CameraManipulatorQtQml::Index
{
public:
    typedef StandardManipulator OType;
    typedef StandardManipulatorQtQml QType;
    friend class StandardManipulatorQtQml;

public:
    Index(StandardManipulator *o = 0);

    void setNode(osg::NodeQtQml *node);
};

}

#endif // _OSGGA_STANDARDMANIPULATOR_QTQML_INDEX_
