set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

add_library( SimpleElastix sitkSimpleElastix.cxx sitkSimpleElastixImpl.h sitkSimpleElastixImpl.cxx )
set_target_properties( SimpleElastix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleElastix INTERFACE elastix )
sitk_install_exported_target( SimpleElastix )

add_library( SimpleTransformix sitkSimpleTransformix.cxx sitkSimpleTransformixImpl.h  sitkSimpleTransformixImpl.cxx )
set_target_properties( SimpleTransformix PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( SimpleTransformix INTERFACE transformix )
sitk_install_exported_target( SimpleTransformix ) 


