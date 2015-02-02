qt5_generate_moc(plugin.cpp plugin.moc)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(osggaplugin MODULE plugin.cpp plugin.moc)

set_target_properties(osggaplugin PROPERTIES
  COMPILE_FLAGS "-DQT_PLUGIN -DQT_NO_DEBUG")

target_link_libraries(osggaplugin osgQtQml Qt5::Qml)

file(WRITE "${CMAKE_BINARY_DIR}/imports/osgGA/qmldir"
  "module osgGA\nplugin osggaplugin\n")

install(FILES
  "${CMAKE_BINARY_DIR}/imports/osgGA/qmldir"
  DESTINATION "imports/osgGA")

install(TARGETS osggaplugin
  LIBRARY DESTINATION "imports/osgGA")
