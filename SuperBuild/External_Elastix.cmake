set( proj ELASTIX )
set( ELASTIX_DEPENDENCIES "ITK")
set( ELASTIX_REPOSITORY git://github.com/kaspermarstal/elastix.git )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_common_cache}" )

ExternalProject_Add( ${proj}
  GIT_REPOSITORY ${ELASTIX_REPOSITORY}
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
  --no-warn-unused-cli
  -C "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
  -DELASTIX_BUILD_TESTING:BOOL=OFF
  -DELASTIX_BUILD_EXECUTABLE:BOOL=OFF
  -DUSE_KNNGraphAlphaMutualInformationMetric:BOOL=OFF
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DITK_DIR:PATH=${ITK_DIR}
  DEPENDS
  ${ELASTIX_DEPENDENCIES}
)

ExternalProject_Get_Property(ELASTIX BINARY_DIR)
set( ELASTIX_USE_FILE "${BINARY_DIR}/src/UseElastix.cmake" )


