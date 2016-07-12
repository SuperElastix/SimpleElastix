cmake_minimum_required(VERSION 2.8)
project(SimpleITKExamples)

foreach(p
    CMP0042 # CMake 3.0
    CMP0063 # CMake 3.3.2
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK")
  find_package(SimpleITK REQUIRED)
  include(${SimpleITK_USE_FILE})

  # Add compiler flags needed to use SimpleITK.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SimpleITK_REQUIRED_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SimpleITK_REQUIRED_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
endif()

add_executable( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${SimpleITK_LIBRARIES} )

add_executable( SimpleElastixCxx SimpleElastix.cxx )
target_link_libraries( SimpleElastixCxx ${SimpleITK_LIBRARIES} )

add_executable( SimpleTransformixCxx SimpleTransformix.cxx )
target_link_libraries( SimpleTransformixCxx ${SimpleITK_LIBRARIES} )

add_executable ( ImageRegistrationMethodDisplacement1 ImageRegistrationMethodDisplacement1.cxx )
target_link_libraries ( ImageRegistrationMethodDisplacement1  ${SimpleITK_LIBRARIES} )

add_executable ( DemonsRegistration1 DemonsRegistration1.cxx )
target_link_libraries ( DemonsRegistration1 ${SimpleITK_LIBRARIES} )

add_executable ( DemonsRegistration2 DemonsRegistration2.cxx )
target_link_libraries ( DemonsRegistration2 ${SimpleITK_LIBRARIES} )

# Add subdirectories
add_subdirectory(Segmentation)

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleITK_BINARY_DIR}/Testing/Temporary)
set(TEST_HARNESS_DATA_DIRECTORY ${SimpleITK_BINARY_DIR}/ExternalData/Testing/Data)
set(ITK_TEST_DRIVER  "itkTestDriver")


macro(add_language_subdirectory lang)
  string(TOUPPER ${lang} LANG)
  if ( WRAP_${LANG} )
    add_subdirectory(${lang})
  endif()
endmacro()

if ( BUILD_TESTING )
  add_subdirectory( test )

  add_language_subdirectory( CSharp )
  add_language_subdirectory( Java )
  add_language_subdirectory( Python )
  add_language_subdirectory( R )
  add_language_subdirectory( Ruby )
  add_language_subdirectory( Tcl )

endif()
