
set(SOURCE_FILES main.cpp
        Router.cpp
        controllers/SongController.cpp
        helper.cpp
        APICredential.cpp
        YoutubeService.cpp
        AddVideoRequest.cpp)

add_executable(LivePlaylist ${SOURCE_FILES})
target_link_libraries(LivePlaylist
        ${GOOGLE_YOUTUBE_LIBRARIES}
        ${CPR_LIBRARIES}
        ${GOOGLE_LIBRARIES}
        jsoncpp
        glog
        ssl
        net_static
        pthread)
