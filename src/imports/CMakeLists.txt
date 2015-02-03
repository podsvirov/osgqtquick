add_subdirectory(osg)
add_subdirectory(osgdb)
add_subdirectory(osgga)
add_subdirectory(osgviewer)

if(osgQtQuick_WITH_EARTH)
  add_subdirectory(osgearthutil)
endif()
