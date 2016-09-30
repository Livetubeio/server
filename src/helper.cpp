//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include <string>
#include <vector>
#include <map>
#include <router.h>


using namespace std;

vector<string> H::split(const string stri, char c = ' ')
{
    auto str = stri.c_str();
    vector<string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}

map<string, string> H::parseRequest(const Net::Rest::Request& request) {
    map<string,string> params;

    auto fields = split(request.body(),'&');
    for(auto param:fields) {
        auto keyValue = split(param,'=');

        params.insert(std::pair<std::string,std::string>(keyValue[0],keyValue[1]));
    }
    return params;
}
