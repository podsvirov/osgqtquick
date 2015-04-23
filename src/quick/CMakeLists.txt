if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQUICK_LIBRARY)
else()
    add_definitions(-DOSGQTQUICK_LIBRARY_STATIC)
endif()

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

qt5_wrap_cpp(_mocs
  object.hpp
  window.hpp
  osgviewer/view.hpp)

add_library(osgQtQuick ${OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC}
  index.cpp
  object.cpp
  window.cpp
  ${_mocs}
# osgViewer
  osgviewer/view.cpp
  osgviewer/module.cpp
)

target_link_libraries(osgQtQuick
    osgQtQml
    ${OPENTHREADS_LIBRARIES}
    ${OSG_LIBRARIES}
    ${OSGVIEWER_LIBRARIES}
    ${OSGGA_LIBRARIES}
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
  INTERFACE_LINK_LIBRARIES "")

install(TARGETS osgQtQuick EXPORT osgQtQuick
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
