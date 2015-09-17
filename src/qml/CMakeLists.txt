if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQML_LIBRARY)
else()
    add_definitions(-DOSGQTQML_LIBRARY_STATIC)
endif()

macro(META_Node _library _class)
  string(TOLOWER ${_library} _library_l)
  string(TOLOWER ${_class} _class_l)
  file(WRITE "${CMAKE_BINARY_DIR}/include/${_library}/${_class}QtQml"
    "#include \"${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp\"\n")
  install(FILES "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp"
    DESTINATION "include/${_library}" RENAME "${_class}QtQml")
  file(WRITE "${CMAKE_BINARY_DIR}/include/${_library}/${_class}QtQmlIndex"
    "#include \"${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}index.hpp\"\n")
  install(FILES "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}index.hpp"
    DESTINATION "include/${_library}" RENAME "${_class}QtQmlIndex")
  list(APPEND _srcs "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.cpp")
  list(APPEND _moc_hdrs "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp")
endmacro(META_Node)

set(_srcs)
set(_moc_hdrs)

META_Node(osg Geode)
META_Node(osg Shape)
META_Node(osg CompositeShape)
META_Node(osg Box)
META_Node(osg Sphere)

META_Node(osgGA StandardManipulator)
META_Node(osgGA FirstPersonManipulator)
META_Node(osgGA FlightManipulator)
META_Node(osgGA OrbitManipulator)
META_Node(osgGA NodeTrackerManipulator)

META_Node(osgText TextBase)

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
# osgText
  osgtext/module.cpp
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
  ${OSGDB_LIBRARIES}
  ${OSGGA_LIBRARIES}
  ${OSGTEXT_LIBRARIES}
  ${OSGVIEWER_LIBRARIES}
  ${OSGEARTHUTIL_LIBRARY}
  Qt5::Gui
  Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Export"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/export.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/export.hpp"
  DESTINATION "include/osgQtQml" RENAME "Export")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Index"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/index.hpp"
  DESTINATION "include/osgQtQml" RENAME "Index")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Object"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/object.hpp"
  DESTINATION "include/osgQtQml" RENAME "Object")


file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/module.hpp"
  DESTINATION "include/osg" RENAME "ModuleQtQml")


file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ObjectQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/object.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/object.hpp"
  DESTINATION "include/osg" RENAME "ObjectQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ObjectQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/objectindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/objectindex.hpp"
  DESTINATION "include/osg" RENAME "ObjectQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NodeQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/node.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/node.hpp"
  DESTINATION "include/osg" RENAME "NodeQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NodeQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/nodeindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/nodeindex.hpp"
  DESTINATION "include/osg" RENAME "NodeQtQmlIndex")

 file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NotifyQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/notify.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/notify.hpp"
  DESTINATION "include/osg" RENAME "NotifyQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NotifyQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/notifyindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/notifyindex.hpp"
  DESTINATION "include/osg" RENAME "NotifyQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GroupQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/group.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/group.hpp"
  DESTINATION "include/osg" RENAME "GroupQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GroupQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/groupindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/groupindex.hpp"
  DESTINATION "include/osg" RENAME "GroupQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/TransformQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/transform.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/transform.hpp"
  DESTINATION "include/osg" RENAME "TransformQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/TransformQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/transformindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/transformindex.hpp"
  DESTINATION "include/osg" RENAME "TransformQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/PositionAttitudeTransformQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/positionattitudetransform.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/positionattitudetransform.hpp"
  DESTINATION "include/osg" RENAME "PositionAttitudeTransformQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/PositionAttitudeTransformQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/positionattitudetransformindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/positionattitudetransformindex.hpp"
  DESTINATION "include/osg" RENAME "PositionAttitudeTransformQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/CameraQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/camera.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/camera.hpp"
  DESTINATION "include/osg" RENAME "CameraQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/CameraQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/cameraindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/cameraindex.hpp"
  DESTINATION "include/osg" RENAME "CameraQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/DrawableQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/drawable.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/drawable.hpp"
  DESTINATION "include/osg" RENAME "DrawableQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/DrawableQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/drawableindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/drawableindex.hpp"
  DESTINATION "include/osg" RENAME "DrawableQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ShapeDrawableQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/shapedrawable.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/shapedrawable.hpp"
  DESTINATION "include/osg" RENAME "ShapeDrawableQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ShapeDrawableQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/shapedrawableindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/shapedrawableindex.hpp"
  DESTINATION "include/osg" RENAME "ShapeDrawableQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GraphicsContextQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/graphicscontext.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/graphicscontext.hpp"
  DESTINATION "include/osg" RENAME "GraphicsContextQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GraphicsContextQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/graphicscontextindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osg/graphicscontextindex.hpp"
  DESTINATION "include/osg" RENAME "GraphicsContextQtQmlIndex")


file(WRITE "${CMAKE_BINARY_DIR}/include/osgDB/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgdb/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgdb/module.hpp"
  DESTINATION "include/osgDB" RENAME "ModuleQtQml")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgDB/LoaderQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgdb/loader.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgdb/loader.hpp"
  DESTINATION "include/osgDB" RENAME "LoaderQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgDB/LoaderQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgdb/loaderindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgdb/loaderindex.hpp"
  DESTINATION "include/osgDB" RENAME "LoaderQtQmlIndex")


file(WRITE "${CMAKE_BINARY_DIR}/include/osgGA/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgga/module.hpp"
  DESTINATION "include/osgGA" RENAME "ModuleQtQml")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgGA/CameraManipulatorQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/cameramanipulator.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgga/cameramanipulator.hpp"
  DESTINATION "include/osgGA" RENAME "CameraManipulatorQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgGA/CameraManipulatorQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/cameramanipulatorindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgga/cameramanipulatorindex.hpp"
  DESTINATION "include/osgGA" RENAME "CameraManipulatorQtQmlIndex")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgGA/TrackballManipulatorQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/trackballmanipulator.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgga/trackballmanipulator.hpp"
  DESTINATION "include/osgGA" RENAME "TrackballManipulatorQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgGA/TrackballManipulatorQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/trackballmanipulatorindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgga/trackballmanipulatorindex.hpp"
  DESTINATION "include/osgGA" RENAME "TrackballManipulatorQtQmlIndex")


file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp"
  DESTINATION "include/osgViewer" RENAME "ModuleQtQml")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/CompositeViewerQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/compositeviewer.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/compositeviewer.hpp"
  DESTINATION "include/osgViewer" RENAME "CompositeViewerQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/CompositeViewerQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/compositeviewerindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/compositeviewerindex.hpp"
  DESTINATION "include/osgViewer" RENAME "CompositeViewerQtQmlIndex")

if(osgQtQuick_WITH_EARTH)

file(WRITE "${CMAKE_BINARY_DIR}/include/osgEarthUtil/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgearthutil/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgearthutil/module.hpp"
  DESTINATION "include/osgEarthUtil" RENAME "ModuleQtQml")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgEarthUtil/EarthManipulatorQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgearthutil/earthmanipulator.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgearthutil/earthmanipulator.hpp"
  DESTINATION "include/osgEarthUtil" RENAME "EarthManipulatorQtQml")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgEarthUtil/EarthManipulatorQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgearthutil/earthmanipulatorindex.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgearthutil/earthmanipulatorindex.hpp"
  DESTINATION "include/osgEarthUtil" RENAME "EarthManipulatorQtQmlIndex")

endif() # osgQtQuick_WITH_EARTH

set_target_properties(osgQtQml PROPERTIES
  INTERFACE_LINK_LIBRARIES "")

install(TARGETS osgQtQml EXPORT osgQtQuick
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
