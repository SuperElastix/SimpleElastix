set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

set( SimpleElastix
  sitkSimpleElastix.cxx
  sitkSimpleElastix.hxx
)

add_library( SimpleElastix ${SimpleElastix} )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleElastix elastix )
sitk_install_exported_target( SimpleElastix )

set( SimpleTransformix
  sitkSimpleTransformix.cxx
  sitkSimpleTransformix.hxx
)

add_library( SimpleTransformix ${SimpleTransformix} )
set_target_properties( SimpleTransformix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleTransformix transformix )
sitk_install_exported_target( SimpleTransformix )
