qt5_generate_moc(plugin.cpp plugin.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(osgdbplugin MODULE plugin.cpp plugin.moc)

set_target_properties(osgdbplugin PROPERTIES
  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

target_link_libraries(osgdbplugin osgQtQml Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osgDB/qmldir"
  "module osgDB\nplugin osgdbplugin\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osgDB/qmldir"
  DESTINATION "imports/osgDB")

install(TARGETS osgdbplugin
  LIBRARY DESTINATION "imports/osgDB")
