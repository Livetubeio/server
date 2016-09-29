//
// Created by stevijo on 29.09.16.
//

#ifndef LIVEPLAYLIST_YOUTUBESERVICE_H
#define LIVEPLAYLIST_YOUTUBESERVICE_H


#include <google/youtube_api/you_tube_service.h>
#include <googleapis/client/transport/http_transport.h>
#include <googleapis/client/transport/curl_http_transport.h>

using namespace googleapis;

class YoutubeService {
public:
    static YoutubeService& instance() {
        static YoutubeService youtubeService;
        return youtubeService;
    }

    static google_youtube_api::YouTubeService* service() {
        return instance().get_service();
    }

    google_youtube_api::YouTubeService* get_service() {
        return service_.get();
    }
private:
    YoutubeService()  {
        config.reset(new client::HttpTransportLayerConfig);
        client::HttpTransportFactory* factory = new client::CurlHttpTransportFactory(config.get());
        config->ResetDefaultTransportFactory(factory);
        service_.reset(new google_youtube_api::YouTubeService(factory->New()));
    }

    std::unique_ptr<google_youtube_api::YouTubeService> service_;
    std::unique_ptr<client::HttpTransportLayerConfig> config;

};


#endif //LIVEPLAYLIST_YOUTUBESERVICE_H
