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
    template<typename T>
    typename T::OType* o(T *p);

    void setO(CameraManipulator *o);

    CameraManipulator *o_ptr;
};

template<typename T>
inline typename T::OType* CameraManipulatorQtQml::Index::o(T *p)
{
    return static_cast<typename T::OType*>(p->o_ptr);
}

inline void CameraManipulatorQtQml::Index::setO(CameraManipulator *o)
{
    o_ptr = o;
    ObjectQtQml::Index::setO(static_cast<osg::NodeCallback*>(o));
}

}

#endif // _OSGGA_CAMERAMANIPULATOR_QTQML_INDEX_
