if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQUICK_LIBRARY)
else()
    add_definitions(-DOSGQTQUICK_LIBRARY_STATIC)
endif()

set(_hdrs
  object.hpp
  window.hpp
  osgviewer/view.hpp)

set(_srcs
  index.cpp
  object.cpp
  window.cpp
# osgViewer
  osgviewer/view.cpp
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

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Export"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/export.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/export.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Export")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Index"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/index.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Index")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Object"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/object.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Object")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Window"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/window.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/window.hpp"
  DESTINATION "include/osgQtQuick" RENAME "Window")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/ModuleQtQuick"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp"
  DESTINATION "include/osgViewer" RENAME "ModuleQtQuick")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/ViewQtQuick"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/view.hpp\"\n")
install(FILES "${CMAKE_CURRENT_LIST_DIR}/osgviewer/view.hpp"
  DESTINATION "include/osgViewer" RENAME "ViewQtQuick")

set_target_properties(osgQtQuick PROPERTIES
  INTERFACE_LINK_LIBRARIES "osgQtQml")

install(TARGETS osgQtQuick EXPORT osgQtQuick
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
