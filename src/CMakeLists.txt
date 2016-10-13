
set(SOURCE_FILES main.cpp
        Router.cpp
        controllers/VideoController.cpp
        controllers/ChannelController.cpp
        controllers/LoginController.cpp
        helper.cpp
        APICredential.cpp
        YoutubeService.cpp
        Github.cpp
        jwt/CertificatesStore.cpp
        jwt/Certificate.cpp
        jwt/Token.cpp
        jwt/TokenVerifier.cpp
        middleware/CorsMiddleware.cpp
        requests/BaseRequest.cpp
        requests/AddVideoRequest.cpp
        requests/UpdateChannelRequest.cpp
        requests/DeleteVideoRequest.cpp
        )

add_executable(LivePlaylist ${SOURCE_FILES})
target_link_libraries(LivePlaylist
        ${GOOGLE_YOUTUBE_LIBRARIES}
        ${CPR_LIBRARIES}
        ${GOOGLE_LIBRARIES}
        ${LIBJWT_LIBRARIES}
        jansson
        jsoncpp
        glog
        ssl
        net_static
        pthread)
