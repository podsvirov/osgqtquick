if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQML_LIBRARY)
else()
    add_definitions(-DOSGQTQML_LIBRARY_STATIC)
endif()

set(_srcs)
set(_moc_hdrs)

# Meta node
macro(META_Node _library _class)
  string(TOLOWER ${_library} _library_l)
  string(TOLOWER ${_class} _class_l)
  file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/${_library}/${_class}QtQml"
    CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp\"\n")
  install(FILES "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp"
    DESTINATION "include/${_library}" RENAME "${_class}QtQml")
  file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/${_library}/${_class}QtQmlIndex"
    CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}index.hpp\"\n")
  install(FILES "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}index.hpp"
    DESTINATION "include/${_library}" RENAME "${_class}QtQmlIndex")
  list(APPEND _srcs "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.cpp")
  list(APPEND _moc_hdrs "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp")
endmacro(META_Node)

META_Node(osg Object)
META_Node(osg Node)
META_Node(osg Group)
META_Node(osg Geode)
META_Node(osg Shape)
META_Node(osg CompositeShape)
META_Node(osg Box)
META_Node(osg Sphere)
META_Node(osg Cylinder)
META_Node(osg Transform)
META_Node(osg MatrixTransform)
META_Node(osg PositionAttitudeTransform)
META_Node(osg Camera)
META_Node(osg Drawable)
META_Node(osg ShapeDrawable)
META_Node(osg GraphicsContext)
META_Node(osg Notify) # Custom type

META_Node(osgDB Loader) # Custom type

META_Node(osgGA CameraManipulator)
META_Node(osgGA StandardManipulator)
META_Node(osgGA FirstPersonManipulator)
META_Node(osgGA FlightManipulator)
META_Node(osgGA OrbitManipulator)
META_Node(osgGA NodeTrackerManipulator)
META_Node(osgGA TrackballManipulator)

META_Node(osgManipulator Dragger)
META_Node(osgManipulator RotateSphereDragger)
META_Node(osgManipulator CompositeDragger)
META_Node(osgManipulator TabPlaneDragger)
META_Node(osgManipulator TabBoxDragger)

META_Node(osgText Style)
META_Node(osgText Font)
META_Node(osgText FontImplementation)
META_Node(osgText TextBase)
META_Node(osgText Text3D)

META_Node(osgQt QFontImplementation)

META_Node(osgViewer CompositeViewer)

set(_hdrs
  object.hpp
  osg/object.hpp
  osg/node.hpp
  osg/notify.hpp
  osg/group.hpp
  osg/transform.hpp
  osg/positionattitudetransform.hpp
  osg/camera.hpp
  osg/drawable.hpp
  osg/shapedrawable.hpp
  osg/graphicscontext.hpp
  osgdb/loader.hpp
  osgdb/loaderindex.hpp
  osgga/cameramanipulator.hpp
  osgga/trackballmanipulator.hpp
  osgviewer/compositeviewer.hpp
  ${_moc_hdrs})

list(APPEND _srcs
  index.cpp
  object.cpp
# osg
  osg/object.cpp
  osg/node.cpp
  osg/notify.cpp
  osg/group.cpp
  osg/transform.cpp
  osg/positionattitudetransform.cpp
  osg/camera.cpp
  osg/drawable.cpp
  osg/shapedrawable.cpp
  osg/graphicscontext.cpp
  osg/module.cpp
# osgDB
  osgdb/loader.cpp
  osgdb/module.cpp
# osgGA
  osgga/cameramanipulator.cpp
  osgga/trackballmanipulator.cpp
  osgga/module.cpp
# osgManipulator
  osgmanipulator/module.cpp
# osgText
  osgtext/module.cpp
# osgQt
  osgqt/module.cpp
# osgViewer
  osgviewer/compositeviewer.cpp
  osgviewer/module.cpp
)

if(osgQtQuick_WITH_EARTH)
  list(APPEND _moc_hdrs
    # osgEarthUtil
    osgearthutil/earthmanipulator.hpp)
  list(APPEND _srcs
    # osgEarthUtil
    osgearthutil/module.cpp
    osgearthutil/earthmanipulator.cpp)
endif()

qt5_wrap_cpp(_mocs
  ${_hdrs}
  ${_moc_hdrs})

source_group(GeneratedFiles FILES ${_mocs})

add_library(osgQtQml ${OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${_hdrs}
  ${_srcs}
  ${_moc_hdrs}
  ${_mocs}
)

osgqtquick_library(osgQtQml)

target_link_libraries(osgQtQml
  ${OPENTHREADS_LIBRARIES}
  ${OSG_LIBRARIES}
  ${OSGQT_LIBRARIES}
  ${OSGDB_LIBRARIES}
  ${OSGGA_LIBRARIES}
  ${OSGMANIPULATOR_LIBRARIES}
  ${OSGTEXT_LIBRARIES}
  ${OSGVIEWER_LIBRARIES}
  ${OSGEARTHUTIL_LIBRARY}
  Qt5::Gui
  Qt5::Qml)

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQml/Export"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/export.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/export.hpp"
  DESTINATION "include/osgQtQml" RENAME "Export")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQml/Index"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/index.hpp"
  DESTINATION "include/osgQtQml" RENAME "Index")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQml/Object"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/object.hpp"
  DESTINATION "include/osgQtQml" RENAME "Object")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osg/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/module.hpp"
  DESTINATION "include/osg" RENAME "ModuleQtQml")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgDB/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgdb/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgdb/module.hpp"
  DESTINATION "include/osgDB" RENAME "ModuleQtQml")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgGA/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgga/module.hpp"
  DESTINATION "include/osgGA" RENAME "ModuleQtQml")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgManipulator/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgmanipulator/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgmanipulator/module.hpp"
  DESTINATION "include/osgManipulator" RENAME "ModuleQtQml")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgText/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgtext/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgtext/module.hpp"
  DESTINATION "include/osgText" RENAME "ModuleQtQml")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQt/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgqt/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgqt/module.hpp"
  DESTINATION "include/osgQt" RENAME "ModuleQtQml")


file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgViewer/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp"
  DESTINATION "include/osgViewer" RENAME "ModuleQtQml")


if(osgQtQuick_WITH_EARTH)

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgEarthUtil/ModuleQtQml"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgearthutil/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgearthutil/module.hpp"
  DESTINATION "include/osgEarthUtil" RENAME "ModuleQtQml")

META_Node(osgEarthUtil EarthManipulator)

endif() # osgQtQuick_WITH_EARTH

set_target_properties(osgQtQml PROPERTIES
  INTERFACE_LINK_LIBRARIES "")

install(TARGETS osgQtQml EXPORT osgQtQuick
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
