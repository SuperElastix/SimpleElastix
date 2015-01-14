# SimpleElastix Examples

if(NOT SimpleITK_SOURCE_DIR)
  # SimpleElastix dependencies
  # selxSimpleElastix.h or selxSimpleTransformix.h requires
  # ITK_USE_FILE and ELASTIX_USE_FILE in addition to SimpleITK
  if( NOT EXISTS ${ELASTIX_USE_FILE} )
    set( ELASTIX_USE_FILE ${ELASTIX_DIR}/UseElastix.cmake )
  endif()
  if( NOT EXISTS ${ELASTIX_USE_FILE} )
    set( ELASTIX_DIR "" CACHE PATH "Path to elastix build folder" )
    message(FATAL_ERROR "Could not find UseElastix.cmake. Point ELASTIX_DIR to folder containing UseElastix.cmake or use SuperBuild.")
  endif()
  include( ${ELASTIX_USE_FILE} )

  find_package( ITK REQUIRED )
  include( ${ITK_USE_FILE} )
endif()

# CXX
add_executable( SimpleElastixCxx SimpleElastix.cxx )
target_link_libraries( SimpleElastixCxx ${SimpleITK_LIBRARIES} elastix )

add_executable( SimpleTransformixCxx SimpleTransformix.cxx )
target_link_libraries( SimpleTransformixCxx ${SimpleITK_LIBRARIES} )

if( WRAP_LUA OR WRAP_PYTHON OR WRAP_JAVA OR WRAP_CSHARP OR WRAP_TCL OR WRAP_R OR WRAP_RUBY )
  find_package ( SWIG 2 REQUIRED )
  include (UseSWIGLocal)
endif()

# Java
find_package( Java )
if( JAVA_FOUND )
  include( UseJava )
  set(CMAKE_JAVA_INCLUDE_PATH ${SimpleITK_INSTALL_PREFIX}/SimpleITK-build/Wrapping)
  add_jar( SimpleElastixJava SimpleElastix.java )
  install_jar( SimpleElastixJava ${CMAKE_BINARY_DIR} )

  add_jar( SimpleTransformixJava SimpleTransformix.java )
  install_jar( SimpleTransformixJava ${CMAKE_BINARY_DIR} )
endif()