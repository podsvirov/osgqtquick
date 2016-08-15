# New policies
foreach(policy CMP0020 CMP0022 CMP0043)
  if(POLICY ${policy})
      cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

list(APPEND CMAKE_MODULE_PATH "${osgQtQuick_ROOT_DIR}/cmake")

# OpenSceneGraph
find_package(OpenSceneGraph 3.0 REQUIRED
  osg
  osgQt
  osgDB
  osgGA
  osgManipulator
  osgUtil
  osgViewer
  osgText)

# Qt
if(osgQtQuick_WITH_QT_PRIVATE)
  find_package(Qt5Quick CONFIG REQUIRED
    COMPONENTS Private)
else()
  find_package(Qt5Quick CONFIG REQUIRED)
endif()

if(osgQtQuick_WITH_EARTH)
  find_package(OsgEarth 2.0 MODULE REQUIRED)
endif()

include(GNUInstallDirs)

if(NOT DEFINED CMAKE_INSTALL_QMLDIR)
  if(NOT EXISTS "${QMAKE_EXECUTABLE}")
    get_target_property(QMAKE_EXECUTABLE Qt5::qmake LOCATION)
  endif()
  execute_process(COMMAND "${QMAKE_EXECUTABLE}" -query QT_INSTALL_PREFIX
    OUTPUT_VARIABLE QT_INSTALL_PREFIX)
  string(STRIP "${QT_INSTALL_PREFIX}" QT_INSTALL_PREFIX)
  execute_process(COMMAND "${QMAKE_EXECUTABLE}" -query QT_INSTALL_QML
    OUTPUT_VARIABLE QT_INSTALL_QML)
  string(STRIP "${QT_INSTALL_QML}" QT_INSTALL_QML)
  file(RELATIVE_PATH CMAKE_INSTALL_QMLDIR
    ${QT_INSTALL_PREFIX} ${QT_INSTALL_QML})
  set(CMAKE_INSTALL_QMLDIR "${CMAKE_INSTALL_QMLDIR}"
    CACHE STRING "qml modules")
endif()

include(osgQtQuickFunctions)

include_directories(
  "${CMAKE_BINARY_DIR}/include"
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
  ${OSGEARTH_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS}
  ${Qt5Quick_INCLUDE_DIRS})

add_subdirectory(qml)
add_subdirectory(quick)

if(osgQtQuick_BUILD_IMPORTS)
  add_subdirectory(imports)
endif()

if(osgQtQuick_BUILD_DEBUGGER)
  add_subdirectory(debugger)
endif()

install(EXPORT osgQtQuick
  DESTINATION "lib/cmake/osgQtQuick"
  FILE osgQtQuickTargets.cmake)
