#ifndef _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_INDEX_
#define _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/FirstPersonManipulatorQtQml>

#include <osgGA/StandardManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT FirstPersonManipulatorQtQml::Index : public StandardManipulatorQtQml::Index
{
public:
    typedef FirstPersonManipulator OType;
    typedef FirstPersonManipulatorQtQml QType;
    friend class FirstPersonManipulatorQtQml;

public:
    Index(FirstPersonManipulator *o = 0);

    void classBegin();
};

}

#endif // _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_INDEX_
