if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQML_LIBRARY)
else()
    add_definitions(-DOSGQTQML_LIBRARY_STATIC)
endif()

qt5_wrap_cpp(_mocs
    object.hpp
    osg/node.hpp
    osg/group.hpp)

message("moc: ${_mocs}")

add_library(osgQtQml ${OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC}
  index.cpp
  object.cpp
  ${_mocs}
# osg
  osg/node.cpp
  osg/group.cpp
  osg/module.cpp
)

target_link_libraries(osgQtQml
    ${OPENTHREADS_LIBRARIES}
    ${OSG_LIBRARIES}
    Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Export"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/export.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Index"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQml/Object"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osg/ModuleQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/module.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NodeQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/node.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/NodeQtQmlIndex"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/nodeindex.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osg/GroupQtQml"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osg/group.hpp\"\n")

install(TARGETS osgQtQml
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
