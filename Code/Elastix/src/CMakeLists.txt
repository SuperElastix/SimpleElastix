set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

add_library( ElastixImageFilter sitkElastixImageFilter.cxx sitkElastixImageFilterImpl.h sitkElastixImageFilterImpl.cxx )
set_target_properties( ElastixImageFilter PROPERTIES SKIP_BUILD_RPATH TRUE )
target_include_directories( ElastixImageFilter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Elastix/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Common/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/Common/include>
    $<INSTALL_INTERFACE:include> )
target_link_libraries( ElastixImageFilter PRIVATE elastix )
sitk_install_exported_target( ElastixImageFilter )

add_library( TransformixImageFilter sitkTransformixImageFilter.cxx sitkTransformixImageFilterImpl.h  sitkTransformixImageFilterImpl.cxx )
set_target_properties( TransformixImageFilter PROPERTIES SKIP_BUILD_RPATH TRUE )
target_include_directories( TransformixImageFilter PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Elastix/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Common/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/Common/include>
    $<INSTALL_INTERFACE:include> )
target_link_libraries( TransformixImageFilter PRIVATE transformix )
sitk_install_exported_target( TransformixImageFilter ) 
