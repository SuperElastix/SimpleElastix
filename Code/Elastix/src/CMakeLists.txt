set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

set( SimpleElastixSource
  sitkSimpleElastix.cxx
  sitkSimpleElastix.hxx
)

add_library( SimpleElastix ${SimpleElastixSource} )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleElastix elastix SimpleITKCommon )
sitk_install_exported_target( SimpleElastix )

set( SimpleTransformixSource
  sitkSimpleTransformix.cxx
  sitkSimpleTransformix.hxx
)

add_library( SimpleTransformix ${SimpleTransformixSource} )
set_target_properties( SimpleTransformix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleTransformix transformix elastix SimpleITKCommon )
sitk_install_exported_target( SimpleTransformix )
