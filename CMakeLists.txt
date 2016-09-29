cmake_minimum_required(VERSION 3.6)
project(LivePlaylist)

set(CMAKE_CXX_STANDARD 14)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)
find_package(gflags)


add_subdirectory(src)