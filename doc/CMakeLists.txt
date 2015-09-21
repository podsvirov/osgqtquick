# Qt
find_package(Qt5 CONFIG
  COMPONENTS Core)

if(NOT TARGET Qt5::qdoc)
  get_target_property(_QT5_BIN_DIR Qt5::qmake IMPORTED_LOCATION)
  get_filename_component(_QT5_BIN_DIR "${_QT5_BIN_DIR}" PATH)
  find_program(_QT5_QDOC_IMPORTED_LOCATION qdoc
    PATHS "${_QT5_BIN_DIR}")
  add_executable(Qt5::qdoc IMPORTED)
  set_target_properties(Qt5::qdoc PROPERTIES
    IMPORTED_LOCATION ${_QT5_QDOC_IMPORTED_LOCATION})
endif()

set(_DOCS_DIR "${CMAKE_CURRENT_LIST_DIR}/html")

if(NOT EXISTS "${_DOCS_DIR}/index.html")
  file(COPY "${CMAKE_CURRENT_LIST_DIR}/src/index.html"
    DESTINATION "${_DOCS_DIR}")
endif()

if(DEFINED _DOC_INDEXES)
  unset(_DOC_INDEXES)
endif()
foreach(_DOC_MODULE osg osgdb osgga osgtext osgviewer osgdoc)
    set(_DOC_INDEX "${_DOCS_DIR}/${_DOC_MODULE}/${_DOC_MODULE}.index")
    add_custom_target(osgDoc_${_DOC_MODULE}
      COMMAND Qt5::qdoc ${_DOC_MODULE}.qdocconf
      WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")
    list(APPEND _DOC_INDEXES "osgDoc_${_DOC_MODULE}")
endforeach()

add_custom_target(osgdocs ALL
  DEPENDS ${_DOC_INDEXES}
  COMMENT "Building osgQtQuick Reference Documentation")

install(DIRECTORY "${_DOCS_DIR}/"
  DESTINATION "share/doc/osgQtQuick/html"
  FILES_MATCHING
    PATTERN "*.html"
    PATTERN "*.css"
    PATTERN "*.png")
