qt5_generate_moc(plugin.cpp plugin.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(myoutputdirectory ${PROJECT_BINARY_DIR}/imports/osgViewer)

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

add_library(osgviewerplugin MODULE plugin.cpp plugin.moc)

set_target_properties(osgviewerplugin PROPERTIES
  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

target_link_libraries(osgviewerplugin osgQtQml osgQtQuick Qt5::Quick)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osgViewer/qmldir"
  "module osgViewer\nplugin osgviewerplugin\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osgViewer/qmldir"
  DESTINATION "imports/osgViewer")

install(TARGETS osgviewerplugin
  LIBRARY DESTINATION "imports/osgViewer")
