//
// Created by stevijo on 28.09.16.
//

#ifndef LIVEPLAYLIST_HELPER_H
#define LIVEPLAYLIST_HELPER_H

#include <string>
#include <vector>
#include <map>
#include <router.h>
#include <googleapis/client/transport/http_response.h>
#include <endpoint.h>

using namespace std;

namespace H {
    vector<string> split(const string stri, char c);

    map<string,string> parseRequest(const Net::Rest::Request&);

    std::string base64decode(std::string string);

    void addCorsHeaders(Net::Http::ResponseWriter& response);
}



#endif //LIVEPLAYLIST_HELPER_H
