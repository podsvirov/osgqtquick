qt5_generate_moc(plugin.cpp plugin.moc)

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
