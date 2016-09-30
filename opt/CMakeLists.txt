add_subdirectory(google-api-cpp-client)
add_subdirectory(pistache)

set(PISTACHE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/pistache/include CACHE INTERNAl "")
add_subdirectory(cpr)