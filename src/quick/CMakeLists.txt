if(DYNAMIC_OSGQTQUICK)
    add_definitions(-DOSGQTQUICK_LIBRARY)
else()
    add_definitions(-DOSGQTQUICK_LIBRARY_STATIC)
endif()

qt5_wrap_cpp(_mocs
  object.hpp
  window.hpp
  osgviewer/view.hpp)

message("moc: ${_mocs}")

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
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Index"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/index.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Object"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/object.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgQtQuick/Window"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/window.hpp\"\n")

file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/ModuleQtQuick"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/module.hpp\"\n")
file(WRITE "${CMAKE_BINARY_DIR}/include/osgViewer/ViewQtQuick"
  "#include \"${CMAKE_CURRENT_LIST_DIR}/osgviewer/view.hpp\"\n")

install(TARGETS osgQtQuick
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")
