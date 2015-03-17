set(osgQtQuick_DEBUGGED_SCRIPT "view.qml"
  CACHE STRING "Debugged qml script")

file(GLOB _scripts RELATIVE "${CMAKE_CURRENT_LIST_DIR}/../../tests"
  "../../tests/*.qml")
set_property(CACHE osgQtQuick_DEBUGGED_SCRIPT PROPERTY STRINGS ${_scripts})

get_filename_component(_script
  "../../tests/${osgQtQuick_DEBUGGED_SCRIPT}" ABSOLUTE)

set(_app_name "osgQtQuickDebugger")

add_executable(${_app_name} main.cpp)

qt5_use_modules(${_app_name} Widgets OpenGL Quick)

target_link_libraries(${_app_name} osgQtQml osgQtQuick)

if(osgQtQuick_WITH_EARTH)
  set_property(TARGET ${_app_name} APPEND PROPERTY
    COMPILE_DEFINITIONS "OSGQTQUICK_WITH_EARTH=1")
endif()

if(EXISTS "${_script}")
  set_property(TARGET ${_app_name} APPEND PROPERTY
    COMPILE_DEFINITIONS "OSGQTQUICK_DEBUGGED_SCRIPT=\"${_script}\"")
endif()
