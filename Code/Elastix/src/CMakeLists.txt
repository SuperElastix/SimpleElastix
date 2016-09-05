set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

add_library( SimpleElastix sitkSimpleElastix.cxx )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleElastix elastix SimpleITKCommon )
sitk_install_exported_target( SimpleElastix )

add_library( SimpleTransformix sitkSimpleTransformix.cxx )
set_target_properties( SimpleTransformix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleTransformix transformix SimpleITKCommon )
sitk_install_exported_target( SimpleTransformix )  
