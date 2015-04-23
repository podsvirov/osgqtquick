qt5_generate_moc(plugin.cpp plugin.moc)

set(myoutputdirectory ${PROJECT_BINARY_DIR}/imports/osg)

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

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(osgplugin MODULE plugin.cpp plugin.moc)

set_target_properties(osgplugin PROPERTIES
  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

target_link_libraries(osgplugin osgQtQml Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osg/qmldir"
  "module osg\nplugin osgplugin\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osg/qmldir"
  DESTINATION "imports/osg")

install(TARGETS osgplugin
  LIBRARY DESTINATION "imports/osg")
