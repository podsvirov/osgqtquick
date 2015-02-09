#ifndef _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_INDEX_
#define _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_INDEX_ 1

#include <osgGA/FirstPersonManipulatorQtQml>

#include <osgGA/StandardManipulatorQtQmlIndex>

namespace osgGA {

class OSGQTQML_EXPORT FirstPersonManipulatorQtQml::Index : public StandardManipulatorQtQml::Index
{
    friend class FirstPersonManipulatorQtQml;

public:
    Index(FirstPersonManipulator *o = 0);

    void classBegin();

protected:
    FirstPersonManipulator *othis;
    FirstPersonManipulatorQtQml *qthis;
};

}

#endif // _OSGGA_FIRSTPERSONMANIPULATOR_QTQML_INDEX_
