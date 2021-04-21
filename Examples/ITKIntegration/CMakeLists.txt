##if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
##  set ( ITK_DIR "../ITK-build" )
##  find_package ( ITK )
##  include( ${ITK_USE_FILE} )
##  find_package ( Elastix )
##  include ( ${ELASTIX_USE_FILE} )
##endif()

# The SimpleITK project only finds ITK, it does not include the use file.
# Thus this needs to be done both when this folder is compiled via the
# main SimpleITK project and when compiled as an external project.
include(${ITK_USE_FILE})

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${ELASTIX_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( TransformixFilter TransformixFilter.cxx )
target_link_libraries( TransformixFilter ${ELASTIX_LIBRARIES} ${ITK_LIBRARIES} )
