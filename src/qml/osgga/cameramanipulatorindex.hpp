#ifndef _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_
#define _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_ 1

#include <osg/ObjectQtQmlIndex>

#include <osgGA/CameraManipulatorQtQml>

#include <osgGA/CameraManipulator>

namespace osgGA {

class OSGQTQML_EXPORT CameraManipulatorQtQml::Index : public ObjectQtQml::Index
{
public:
    typedef CameraManipulator OType;
    typedef CameraManipulatorQtQml QType;
    friend class CameraManipulatorQtQml;

public:
    Index(CameraManipulator *o = 0);

protected:
    template<typename T, typename O = typename T::OType>
    O* o(T *p);

    void setO(CameraManipulator *o);

    CameraManipulator *othis;
};

template<typename T, typename O>
inline O* CameraManipulatorQtQml::Index::o(T *p)
{
    return static_cast<O*>(p->othis);
}

inline void CameraManipulatorQtQml::Index::setO(CameraManipulator *o)
{
    othis = o;
    ObjectQtQml::Index::setO(static_cast<osg::NodeCallback*>(o));
}

}

#endif // _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_
