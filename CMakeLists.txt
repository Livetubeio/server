cmake_minimum_required(VERSION 3.2)
project(LivePlaylist)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(opt)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories (${PISTACHE_INCLUDE_DIRS})
include_directories (${SOCKETIO_INCLUDE_DIRS})
include_directories (${GOOGLE_INCLUDE_DIRS})
include_directories (${CPR_INCLUDE_DIRS})
include_directories (${GOOGLE_YOUTUBE_INCLUDE_DIRS})
include_directories (${LIBJWT_INCLUDE_DIRS})
include_directories (${RAPIDJSON_INCLUDE_DIRS})
find_package(gflags)

add_subdirectory(src)
