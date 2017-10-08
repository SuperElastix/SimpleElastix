if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  find_package ( ITK )
  include( ${ITK_USE_FILE} )
  find_package ( Elastix )
  include ( ${ELASTIX_USE_FILE} )
endif()

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${ELASTIX_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( TransformixFilter TransformixFilter.cxx )
target_link_libraries( TransformixFilter ${ELASTIX_LIBRARIES} ${ITK_LIBRARIES} )
