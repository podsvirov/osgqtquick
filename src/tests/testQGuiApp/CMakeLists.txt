qt5_generate_moc(main.cpp main.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

SET(APP_NAME testQGuiApp)

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

ADD_EXECUTABLE(${APP_NAME} main.cpp main.moc)

qt5_use_modules(${APP_NAME} Widgets OpenGL Declarative Quick)

#set_target_properties(${APP_NAME} PROPERTIES
#  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

#target_link_libraries(${APP_NAME} osgQtQml Qt5::Qml)

#file(WRITE "${CMAKE_BINARY_DIR}/imports/osg/qmldir"
#  "module osg\nplugin osgplugin\n")

#install(FILES
#  "${CMAKE_BINARY_DIR}/imports/osg/qmldir"
#  DESTINATION "imports/osg")

#install(TARGETS osgplugin
#  LIBRARY DESTINATION "imports/osg")




