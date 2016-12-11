#ifndef LIVEPLAYLIST_YOUTUBESERVICE_H
#define LIVEPLAYLIST_YOUTUBESERVICE_H


#include <google/youtube_api/you_tube_service.h>
#include <googleapis/client/transport/http_transport.h>
#include <googleapis/client/transport/curl_http_transport.h>

using namespace googleapis;

class YoutubeService {
public:
    static YoutubeService& instance();

    static google_youtube_api::YouTubeService* service();

    google_youtube_api::YouTubeService* get_service();
private:
    YoutubeService();

    std::unique_ptr<google_youtube_api::YouTubeService> service_;
    std::unique_ptr<client::HttpTransportLayerConfig> config;

};


#endif
