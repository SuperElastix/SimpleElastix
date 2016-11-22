
find_package(ITK REQUIRED ) 
include(${ITK_USE_FILE})

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( TransformixFilter TransformixFilter.cxx )
target_link_libraries( TransformixFilter ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )
