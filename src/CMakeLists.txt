
set(SOURCE_FILES main.cpp
        Router.cpp
        controllers/VideoController.cpp
        controllers/ChannelController.cpp
        helper.cpp
        APICredential.cpp
        YoutubeService.cpp
        requests/BaseRequest.cpp
        requests/AddVideoRequest.cpp
        requests/ChangePlayerStateRequest.cpp
        requests/ChangeActiveVideosRequest.cpp
        )

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
