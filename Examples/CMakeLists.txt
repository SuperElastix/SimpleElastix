cmake_minimum_required(VERSION 2.8)
project( SimpleElastixExamples )

if( NOT SimpleITK_SOURCE_DIR )
  find_package( SimpleITK REQUIRED )
  include( ${SimpleITK_USE_FILE} )

  # TODO: CMake refuses to properly configure the ITK_USE_FILE when 
  # called in the SimpleITK_USE_FILE. Here we import ITK manually, but
  # really all dependencies should be resolved by the SimpleITK_USE_FILE.
  find_package( ITK REQUIRED )
  include( ${ITK_USE_FILE} )

  # Add compiler flags needed to use SimpleITK.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SimpleITK_REQUIRED_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SimpleITK_REQUIRED_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
else()
  set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
  include( ${ITK_USE_FILE} )
endif()

add_executable( SimpleElastixCxx SimpleElastix.cxx )
target_link_libraries( SimpleElastixCxx ${SimpleITK_LIBRARIES} )

add_executable( SimpleTransformixCxx SimpleTransformix.cxx )
target_link_libraries( SimpleTransformixCxx ${SimpleITK_LIBRARIES} )

add_executable( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${SimpleITK_LIBRARIES} )