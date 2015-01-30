qt5_generate_moc(plugin.cpp plugin.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

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
