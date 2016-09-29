
set(SOURCE_FILES main.cpp
        Router.cpp
        controllers/SongController.cpp
        helper.cpp
        APICredential.cpp
        YoutubeService.cpp)

add_executable(LivePlaylist ${SOURCE_FILES})
target_link_libraries(LivePlaylist
        google_youtube_api
        googleapis_curl_http
        googleapis_openssl_codec
        jsoncpp
        googleapis_jsoncpp
        googleapis_http
        googleapis_json
        googleapis_scribes
        googleapis_utils
        googleapis_internal
        glog
        curl
        ssl
        net_static
        pthread)
