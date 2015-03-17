cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0022 NEW)

# OpenSceneGraph
find_package(OpenSceneGraph 3.0 REQUIRED
  osg
  osgDB
  osgGA
  osgUtil
  osgViewer
  osgText)

# Qt
find_package(Qt5 CONFIG
  COMPONENTS Core Qml Quick)

if(osgQtQuick_WITH_EARTH)
  list(APPEND CMAKE_MODULE_PATH "${osgQtQuick_ROOT_DIR}/cmake")
  find_package(OsgEarth 2.0 MODULE REQUIRED)
endif()

include_directories(
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
  ${OSGEARTH_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS}
  ${Qt5Quick_INCLUDE_DIRS})

add_subdirectory(qml)
add_subdirectory(quick)

add_subdirectory(imports)

if(osgQtQuick_BUILD_DEBUGGER)
  add_subdirectory(debugger)
endif()

install(EXPORT osgQtQuick
  DESTINATION "lib/cmake/osgQtQuick"
  FILE osgQtQuickTargets.cmake)
