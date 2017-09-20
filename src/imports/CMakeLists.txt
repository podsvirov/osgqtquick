add_subdirectory(osg)
add_subdirectory(osgdb)
add_subdirectory(osgga)
add_subdirectory(osgmanipulator)
add_subdirectory(osgtext)
add_subdirectory(osgviewer)

if(osgQtQuick_WITH_OSGQT)
  add_subdirectory(osgqt)
endif()

if(osgQtQuick_WITH_EARTH)
  add_subdirectory(osgearthutil)
endif()
