add_subdirectory(google-api-cpp-client)

set(PISTACHE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/pistache/include CACHE INTERNAl "")
add_subdirectory(pistache)

find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()
set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
add_subdirectory(cpr)

add_subdirectory(libjwt)
set(LIBJWT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libjwt/include CACHE INTERNAL "")
set(LIBJWT_LIBRARIES jwt_static CACHE INTERNAL "")