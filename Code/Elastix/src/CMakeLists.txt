set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )
include( ${ELASTIX_USE_FILE} )

set( SimpleElastix
  selxSimpleElastix.cxx
  selxSimpleElastix.hxx
)

add_library( SimpleElastix ${SimpleElastix} )
target_link_libraries ( SimpleElastix elastix )
sitk_install_exported_target( SimpleElastix )

set( SimpleTransformix
  selxSimpleTransformix.cxx
  selxSimpleTransformix.hxx
)

add_library( SimpleTransformix ${SimpleTransformix} )
target_link_libraries ( SimpleTransformix transformix )
sitk_install_exported_target( SimpleTransformix )

