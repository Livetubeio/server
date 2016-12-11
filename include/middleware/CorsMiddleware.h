#ifndef LIVEPLAYLIST_CORSMIDDLEWARE_H
#define LIVEPLAYLIST_CORSMIDDLEWARE_H

#include <endpoint.h>

/**
 * Middleware responsible for setting CORS headers in request
 */
class CorsMiddleware : public Net::Http::Middleware {
public:

    void handleAfter(Net::Http::ResponseWriter& response, std::function<void()> next) override;

};

#endif
