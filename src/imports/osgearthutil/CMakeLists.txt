qt5_generate_moc(plugin.cpp plugin.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(osgearthutilplugin MODULE plugin.cpp plugin.moc)

set_target_properties(osgearthutilplugin PROPERTIES
  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

target_link_libraries(osgearthutilplugin osgQtQml Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osgEarthUtil/qmldir"
  "module osgEarthUtil\nplugin osgearthutilplugin\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osgEarthUtil/qmldir"
  DESTINATION "imports/osgEarthUtil")

install(TARGETS osgearthutilplugin
  LIBRARY DESTINATION "imports/osgEarthUtil")
