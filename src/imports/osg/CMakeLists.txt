project(osgplugin)
SET(PLUGIN_NAME osgplugin)

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

add_library(${PLUGIN_NAME} MODULE plugin.cpp plugin.moc)

# Why are these needed? DQT_NO_DEBUG causes mixing debug and release errors
set_target_properties(${PLUGIN_NAME} PROPERTIES
  COMPILE_FLAGS "-DQT_PLUGIN")#-DQT_NO_DEBUG")

target_link_libraries(${PLUGIN_NAME} osgQtQml Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osg/qmldir"
  "module osg\nplugin ${PLUGIN_NAME}\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osg/qmldir"
  DESTINATION "imports/osg")

install(TARGETS ${PLUGIN_NAME}
  LIBRARY DESTINATION "imports/osg")

 # Create plugin.qmltypes file DOES NOT WORK CORRECTLY YET, why?????
IF(QML_PLUGIN_DUMP_EXE)
	GET_FILENAME_COMPONENT(QT_PATH ${QML_PLUGIN_DUMP_EXE} PATH)
	GET_FILENAME_COMPONENT(OSG_LIBRARY_PATH ${OSG_LIBRARY} PATH)
	ADD_CUSTOM_COMMAND(TARGET ${PLUGIN_NAME}
			  POST_BUILD
			  #COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" ${EXECUTABLE_OUTPUT_PATH}/${PLUGIN_NAME}/qmldir
			  COMMAND CD ${CMAKE_BINARY_DIR}/imports
			  COMMAND SET QT_PLUGIN_PATH=${QT_PATH}/../plugins
			  COMMAND SET QML2_IMPORT_PATH=${QT_PATH}/../qml
			  COMMAND SET PATH=${QT_PATH}\;${OSG_LIBRARY_PATH}/../bin\;${CMAKE_BINARY_DIR}/bin\;${CMAKE_BINARY_DIR}/imports/osg\;%PATH%
			  COMMAND ${QML_PLUGIN_DUMP_EXE} osg "${osgQtQuick_VERSION_MAJOR}.${osgQtQuick_VERSION_MINOR}" ./osg/$<TARGET_FILE_NAME:${PLUGIN_NAME}> > ./osg/plugins.qmltypes -notrelocatable
			  COMMENT "Please build the release configuration as well to generate the plugins.qmltypes file"
	)
ENDIF(QML_PLUGIN_DUMP_EXE)