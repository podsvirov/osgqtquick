cmake_minimum_required(VERSION 2.8)

project(osgQtQuick CXX)

set(osgQtQuick_VERSION_MAJOR 2)
set(osgQtQuick_VERSION_MINOR 0)
set(osgQtQuick_VERSION_PATCH 0)
set(osgQtQuick_VERSION_TWEAK 7)

set(osgQtQuick_BUILD_IMPORTS ON
  CACHE BOOL "Set to ON to build plugins for imported modules (By default is ON)")

set(osgQtQuick_BUILD_DOCS OFF
  CACHE BOOL "Set to ON to build reference documentation (By default is OFF)")

set(osgQtQuick_BUILD_DEBUGGER OFF
  CACHE BOOL "Set to ON to build debugger application (By default is OFF)")

set(osgQtQuick_WITH_EARTH OFF
  CACHE BOOL "Set to ON to build with osgEarth library support (By default is OFF)")

set(osgQtQuick_VERSION
  ${osgQtQuick_VERSION_MAJOR}
  ${osgQtQuick_VERSION_MINOR}
  ${osgQtQuick_VERSION_PATCH}
  ${osgQtQuick_VERSION_TWEAK})
string(REPLACE ";" "." osgQtQuick_VERSION "${osgQtQuick_VERSION}")

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX  "d")
endif()

set(osgQtQuick_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in"
    "${CMAKE_BINARY_DIR}/include/osgQtQuick/Version" @ONLY)
install(FILES "${CMAKE_BINARY_DIR}/include/osgQtQuick/Version"
  DESTINATION "include/osgQtQuick")

configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/osgQtQuickConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/lib/cmake/osgQtQuick/osgQtQuickConfig.cmake" @ONLY)
install(FILES "${CMAKE_BINARY_DIR}/lib/cmake/osgQtQuick/osgQtQuickConfig.cmake"
  DESTINATION "lib/cmake/osgQtQuick")

configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/osgQtQuickConfigVersion.cmake.in"
    "${CMAKE_BINARY_DIR}/lib/cmake/osgQtQuick/osgQtQuickConfigVersion.cmake" @ONLY)
install(FILES "${CMAKE_BINARY_DIR}/lib/cmake/osgQtQuick/osgQtQuickConfigVersion.cmake"
  DESTINATION "lib/cmake/osgQtQuick")

include_directories("${CMAKE_BINARY_DIR}/include")

if(DEFINED DYNAMIC_OPENSCENEGRAPH)
  set(DYNAMIC_OSGQTQUICK ${DYNAMIC_OPENSCENEGRAPH})
else()
  set(DYNAMIC_OSGQTQUICK ON)
endif()

if(DYNAMIC_OSGQTQUICK)
  set(OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC "SHARED")
else()
  set(OSGQTQUICK_USER_DEFINED_DYNAMIC_OR_STATIC "STATIC")
endif()

add_subdirectory(src)

if(osgQtQuick_BUILD_DOCS)
  add_subdirectory(doc)
endif()
