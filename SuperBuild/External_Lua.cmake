# Make sure this file is included only once
get_filename_component(CMAKE_CURRENT_LIST_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
if(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED)
  return()
endif()
set(${CMAKE_CURRENT_LIST_FILENAME}_FILE_INCLUDED 1)

set(proj Lua)

set(lua_TARGET_VERSION 5.1.5)
set(lua_DOWNLOAD_SOURCE_HASH "2e115fe26e435e33b0d5c022e4490567")


# follow the standard EP_PREFIX locations
set(lua_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-build)
set(lua_source_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj})
set(lua_install_dir ${CMAKE_CURRENT_BINARY_DIR}/${proj})
sitkSourceDownload(lua_URL "lua-${lua_TARGET_VERSION}.tar.gz" ${lua_DOWNLOAD_SOURCE_HASH})


file(WRITE "${lua_binary_dir}/CMakeCacheInit.txt" "${ep_common_cache}" )

set(lua_PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/lua.cmake
  ${lua_source_dir}/CMakeLists.txt
)

ExternalProject_Add(Lua
  URL "${lua_URL}"
  URL_HASH MD5=${lua_DOWNLOAD_SOURCE_HASH}
  PATCH_COMMAND ${lua_PATCH_COMMAND}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}
    --no-warn-unused-cli
    -C "${lua_binary_dir}/CMakeCacheInit.txt"
    ${ep_common_args}
    -D BUILD_SHARED_LIBS:BOOL=OFF
    -D CMAKE_INSTALL_PREFIX:PATH=${lua_install_dir}
    ${External_Project_USES_TERMINAL}
)

sitkSourceDownloadDependency(Lua)


set(SimpleITK_LUA_EXECUTABLE  "${lua_install_dir}/bin/lua")
