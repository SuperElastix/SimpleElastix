# TODO: Why is ${ELASTIX_USE_FILE} specified in external configuration superbuild ignored?
set( ELASTIX_USE_FILE_FULLPATH "${CMAKE_BINARY_DIR}/../ELASTIX-build/src${ELASTIX_USE_FILE}" )

if( EXISTS ${ELASTIX_USE_FILE_FULLPATH} )
  include( ${ELASTIX_USE_FILE_FULLPATH} )
else()
  message(FATAL_ERROR "Could not find UseElastix.cmake in " ${ELASTIX_USE_FILE_FULLPATH} )
endif()

set( SimpleElastix
  selxSimpleElastix.cxx
)

include( ${ITK_USE_FILE} )
include( ${ELASTIX_USE_FILE_FULLPATH} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( SimpleElastix ${SimpleElastix} )
target_link_libraries ( SimpleElastix elastix transformix )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )

sitk_install_exported_target( SimpleElastix )