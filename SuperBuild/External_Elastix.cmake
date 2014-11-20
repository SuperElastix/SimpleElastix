set( proj ELASTIX )
set( ELASTIX_DEPENDENCIES "ITK")
set( ELASTIX_REPOSITORY git://github.com/kaspermarstal/elastix.git )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_common_cache}" )

ExternalProject_Add( ${proj}
  GIT_REPOSITORY ${ELASTIX_REPOSITORY}
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}/src
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
  --no-warn-unused-cli
  -DELASTIX_BUILD_TESTING:BOOL=OFF
  -DELASTIX_BUILD_EXECUTABLE=OFF
  -DELASTIX_KNN_ALLOW_SELF_MATCH=BOOL:OFF
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  DEPENDS
  ${ELASTIX_DEPENDENCIES}
)



