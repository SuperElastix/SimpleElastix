


set(proj SimpleITKExamples)

# Set dependency list
set(SimpleITKExamples_DEPENDENCIES "SimpleITK" "elastix")

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_common_cache}" )

ExternalProject_Add(${proj}
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Examples
  BINARY_DIR ${proj}-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    --no-warn-unused-cli
    -C "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt"
    ${ep_common_args}
    -DSimpleITK_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/SimpleITK-0.9/
    -DCMAKE_SKIP_RPATH:BOOL=ON
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DITK_DIR:PATH=${ITK_DIR}
    -DELASTIX_USE_FILE:PATH=${ELASTIX_USE_FILE}
  BUILD_COMMAND ${BUILD_COMMAND_STRING}
  INSTALL_COMMAND ""
  DEPENDS "${SimpleITKExamples_DEPENDENCIES}"
  )
