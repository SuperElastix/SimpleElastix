add_executable( SimpleElastixCxx SimpleElastix.cxx )
target_link_libraries( SimpleElastixCxx ${SimpleITK_LIBRARIES} )

add_executable( SimpleTransformixCxx SimpleTransformix.cxx )
target_link_libraries( SimpleTransformixCxx ${SimpleITK_LIBRARIES} )

add_executable( Example1 Example1.cxx )
target_link_libraries( Example1 ${SimpleITK_LIBRARIES} )