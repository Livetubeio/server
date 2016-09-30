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

using namespace std;

struct H {
    static vector<string> split(const string stri, char c);

    static map<string,string> parseRequest(const Net::Rest::Request&);

};



#endif //LIVEPLAYLIST_HELPER_H
