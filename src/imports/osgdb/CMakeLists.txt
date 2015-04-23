qt5_generate_moc(plugin.cpp plugin.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(myoutputdirectory ${PROJECT_BINARY_DIR}/imports/osgDB)

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${myoutputdirectory} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${myoutputdirectory} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${myoutputdirectory} )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${myoutputdirectory} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${myoutputdirectory} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${myoutputdirectory} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

add_library(osgdbplugin MODULE plugin.cpp plugin.moc)

# Why are these needed? DQT_NO_DEBUG causes mixing debug and release errors
#set_target_properties(osgdbplugin PROPERTIES
#  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

target_link_libraries(osgdbplugin osgQtQml Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osgDB/qmldir"
  "module osgDB\nplugin osgdbplugin\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osgDB/qmldir"
  DESTINATION "imports/osgDB")

install(TARGETS osgdbplugin
  LIBRARY DESTINATION "imports/osgDB")
