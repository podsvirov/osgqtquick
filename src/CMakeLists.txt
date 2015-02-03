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

include_directories(
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS}
  ${Qt5Quick_INCLUDE_DIRS})

add_subdirectory(qml)
add_subdirectory(quick)

add_subdirectory(imports)

install(EXPORT osgQtQuick
  DESTINATION "lib/cmake/osgQtQuick"
  FILE osgQtQuickTargets.cmake)
