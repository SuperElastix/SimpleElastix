set( SimpleElastix
  selxSimpleElastix.cxx
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )
include( ${ELASTIX_USE_FILE} )

add_library( SimpleElastix ${SimpleElastix} )
target_link_libraries ( SimpleElastix elastix transformix )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )

sitk_install_exported_target( SimpleElastix )