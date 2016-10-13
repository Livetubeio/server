//
// Created by stevijo on 13.10.16.
//

#ifndef LIVEPLAYLIST_CORSMIDDLEWARE_H
#define LIVEPLAYLIST_CORSMIDDLEWARE_H

#include <endpoint.h>

class CorsMiddleware : public Net::Http::Middleware {
public:

    void handleAfter(Net::Http::ResponseWriter& response, std::function<void()> next) override;

};


#endif //LIVEPLAYLIST_CORSMIDDLEWARE_H
