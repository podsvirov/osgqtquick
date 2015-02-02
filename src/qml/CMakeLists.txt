if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQML_LIBRARY)
else()
    add_definitions(-DOSGQTQML_LIBRARY_STATIC)
endif()

qt5_wrap_cpp(_mocs
  object.hpp
  osg/object.hpp
  osg/node.hpp
  osg/group.hpp
  osg/transform.hpp
  osg/camera.hpp
  osg/graphicscontext.hpp
  osgga/cameramanipulator.hpp
  osgga/trackballmanipulator.hpp
  osgviewer/compositeviewer.hpp)

message("moc: ${_mocs}")

add_library(osgQtQml ${OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC}
  index.cpp
  object.cpp
  ${_mocs}
# osg
  osg/object.cpp
  osg/node.cpp
  osg/group.cpp
  osg/transform.cpp
  osg/camera.cpp
  osg/graphicscontext.cpp
  osg/module.cpp
# osgGA
  osgga/cameramanipulator.cpp
  osgga/trackballmanipulator.cpp
  osgga/module.cpp
# osgViewer
  osgviewer/compositeviewer.cpp
  osgviewer/module.cpp
)

target_link_libraries(osgQtQml
    ${OPENTHREADS_LIBRARIES}
    ${OSG_LIBRARIES}
    ${OSGGA_LIBRARIES}
    ${OSGVIEWER_LIBRARIES}
    Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Export"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/export.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Index"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Object"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/module.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ObjectQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/object.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ObjectQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/Objectindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NodeQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/node.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NodeQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/nodeindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GroupQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/group.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GroupQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/groupindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/TransformQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/transform.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/TransformQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/transformindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/CameraQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/camera.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/CameraQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/cameraindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GraphicsContextQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/graphicscontext.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GraphicsContextQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/graphicscontextindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgGA/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/module.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgga/CameraManipulatorQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/cameramanipulator.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgga/CameraManipulatorQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/cameramanipulatorindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgga/TrackballManipulatorQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/trackballmanipulator.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgga/TrackballManipulatorQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgga/trackballmanipulatorindex.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/CompositeViewerQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/compositeviewer.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/CompositeViewerQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/compositeviewerindex.hpp\"\n")


install(TARGETS osgQtQml
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
