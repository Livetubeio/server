#include "services/YoutubeService.h"

YoutubeService::YoutubeService() {
    config.reset(new client::HttpTransportLayerConfig);
    client::HttpTransportFactory* factory = new client::CurlHttpTransportFactory(config.get());
    config->ResetDefaultTransportFactory(factory);
    service_.reset(new google_youtube_api::YouTubeService(factory->New()));
}

YoutubeService &YoutubeService::instance() {
    static YoutubeService youtubeService;
    return youtubeService;
}

google_youtube_api::YouTubeService *YoutubeService::service() {
    return instance().get_service();
}

google_youtube_api::YouTubeService *YoutubeService::get_service() {
    return service_.get();
}
