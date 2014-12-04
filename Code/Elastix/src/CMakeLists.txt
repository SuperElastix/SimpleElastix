set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )
include( ${ELASTIX_USE_FILE} )

set( SimpleElastix
  selxSimpleElastix.cxx
  selxSimpleElastix.hxx
  selxParameterMapInterface.cxx
)

add_library( SimpleElastix ${SimpleElastix} )
target_link_libraries ( SimpleElastix elastix )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )
sitk_install_exported_target( SimpleElastix )

set( SimpleTransformix
  selxSimpleTransformix.cxx
)

add_library( SimpleTransformix ${SimpleTransformix} )
target_link_libraries ( SimpleTransformix transformix )
set_target_properties( SimpleTransformix PROPERTIES SKIP_BUILD_RPATH TRUE )
sitk_install_exported_target( SimpleTransformix )

