//
// Created by stevijo on 13.10.16.
//

#include "middleware/CorsMiddleware.h"
#include "header/AccessControlAllowOrigin.h"
#include "header/AccessControlAllowMethods.h"
#include "header/AccessControlMaxAge.h"
#include "header/AccessControlAllowHeaders.h"

void CorsMiddleware::handleAfter(Net::Http::ResponseWriter &response, std::function<void()> next) {
    response.headers().add(
            std::make_shared<AccessControlAllowOrigin>(
                    std::initializer_list<std::string>{"*"})
    );
    response.headers().add(
            std::make_shared<AccessControlAllowMethods>(
                    std::initializer_list<std::string>{"GET","POST","PUT","DELETE"}
            )
    );
    response.headers().add(
            std::make_shared<AccessControlMaxAge>(2629744)
    );
    response.headers().add(
            std::make_shared<AccessControlAllowHeaders>(
                    std::initializer_list<std::string>{"X-LIVETUBE-AUTH","X-GITHUB-AUTH"}
            )
    );
    next();
}
