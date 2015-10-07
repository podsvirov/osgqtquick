#ifndef _OSGGA_ORBITMANIPULATOR_QTQML_INDEX_
#define _OSGGA_ORBITMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/OrbitManipulatorQtQml>

#include <osgGA/StandardManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT OrbitManipulatorQtQml::Index : public StandardManipulatorQtQml::Index
{
public:
    typedef OrbitManipulator OType;
    typedef OrbitManipulatorQtQml QType;
    friend class OrbitManipulatorQtQml;

public:
    Index(OrbitManipulator *o = 0);

    void classBegin();
};

}

#endif // _OSGGA_ORBITMANIPULATOR_QTQML_INDEX_
