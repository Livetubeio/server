//
// Created by stevijo on 04.10.16.
//

#include "Github.h"
#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <algorithm>
#include <iostream>

std::map<std::string,std::vector<std::string>> channelMap{};

bool Github::userOwnsChannel(const std::string &channel) {
    using namespace rapidjson;

    auto channels = channelMap.find(token);
    if(channels != end(channelMap)) {
        std::cout << "vector existing" << std::endl;
        auto pos = find(begin(channels->second),end(channels->second),channel);
        if(pos != end(channels->second)) {
            return true;
        }
    } else {
        auto it = channelMap.insert(std::pair<std::string,std::vector<std::string>>(token, std::vector<std::string>()));
        channels = it.first;
    }
    auto result = cpr::Get(cpr::Url{"https://api.github.com/user"},
             cpr::Parameters{{"access_token",token}});
    Document userData;
    userData.Parse(result.text.c_str());
    result = cpr::Get(cpr::Url{userData["repos_url"].GetString()},cpr::Parameters{{"access_token", token}});

    Document repos;
    repos.Parse(result.text.c_str());

    auto repoArray = repos.GetArray();
    for(auto& value:repoArray) {
        channels->second.push_back(value.GetObject()["full_name"].GetString());
    }

    result = cpr::Get(cpr::Url{userData["organizations_url"].GetString()},cpr::Parameters{{"access_token", token}});
    Document orgs;
    orgs.Parse(result.text.c_str());

    for(auto& value:orgs.GetArray()) {
        result = cpr::Get(cpr::Url{value.GetObject()["repos_url"].GetString()},cpr::Parameters{{"access_token", token}});
        Document org;
        org.Parse(result.text.c_str());
        for(auto& repo:org.GetArray()) {
            channels->second.push_back(repo.GetObject()["full_name"].GetString());
        }
    }

    auto pos = find(begin(channels->second),end(channels->second),channel);
    return pos != end(channels->second);
}
