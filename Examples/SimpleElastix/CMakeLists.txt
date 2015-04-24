find_package( OpenMP )

if( OPENMP_FOUND )
  set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif()

add_executable( SimpleElastixCxx SimpleElastix.cxx )
target_link_libraries( SimpleElastixCxx ${SimpleITK_LIBRARIES} )

add_executable( SimpleTransformixCxx SimpleTransformix.cxx )
target_link_libraries( SimpleTransformixCxx ${SimpleITK_LIBRARIES} )

add_executable( Example1 Example1.cxx )
target_link_libraries( Example1 ${SimpleITK_LIBRARIES} )