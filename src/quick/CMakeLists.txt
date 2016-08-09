if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQUICK_LIBRARY)
else()
    add_definitions(-DOSGQTQUICK_LIBRARY_STATIC)
endif()

include_directories(${Qt5Quick_PRIVATE_INCLUDE_DIRS})

set(_srcs)
set(_moc_hdrs)

# Meta node
macro(META_Node _library _class)
  string(TOLOWER ${_library} _library_l)
  string(TOLOWER ${_class} _class_l)
  file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/${_library}/${_class}QtQuick"
    CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp\"\n")
  install(FILES "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp"
    DESTINATION "include/${_library}" RENAME "${_class}QtQuick")
  file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/${_library}/${_class}QtQuickIndex"
    CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}index.hpp\"\n")
  install(FILES "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}index.hpp"
    DESTINATION "include/${_library}" RENAME "${_class}QtQuickIndex")
  list(APPEND _srcs "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.cpp")
  list(APPEND _moc_hdrs "${CMAKE_CURRENT_LIST_DIR}/${_library_l}/${_class_l}.hpp")
endmacro(META_Node)

META_Node(osgViewer View)

set(_hdrs
  object.hpp
  texturenode.hpp
  renderthread.hpp
  window.hpp
  ${_moc_hdrs})

list(APPEND _srcs
  index.cpp
  object.cpp
  texturenode.cpp
  renderthread.cpp
  window.cpp
# osgViewer
  osgviewer/module.cpp
)

qt5_wrap_cpp(_mocs
  ${_hdrs}
)

source_group(GeneratedFiles FILES ${_mocs})

add_library(osgQtQuick ${OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC}
  ${_hdrs}
  ${_srcs}
  ${_mocs}
)

osgqtquick_library(osgQtQuick)

target_link_libraries(osgQtQuick
    osgQtQml
    ${OPENTHREADS_LIBRARIES}
    ${OSG_LIBRARIES}
    ${OSGVIEWER_LIBRARIES}
    ${OSGGA_LIBRARIES}
    ${OSGDB_LIBRARIES}
    Qt5::Qml
    Qt5::Quick)

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQuick/Export"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/export.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/export.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Export")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQuick/Index"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/index.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Index")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQuick/Object"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/object.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Object")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQuick/TextureNode"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/texturenode.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/texturenode.hpp"
  DESTINATION "include/osgQtQuick" RENAME "TextureNode")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQuick/RenderThread"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/renderthread.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/renderthread.hpp"
  DESTINATION "include/osgQtQuick" RENAME "RenderThread")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgQtQuick/Window"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/window.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/window.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Window")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/include/osgViewer/ModuleQtQuick"
  CONTENT "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp"
  DESTINATION "include/osgViewer" RENAME "ModuleQtQuick")

set_target_properties(osgQtQuick PROPERTIES
  INTERFACE_LINK_LIBRARIES "osgQtQml")

install(TARGETS osgQtQuick EXPORT osgQtQuick
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
