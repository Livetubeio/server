//
// Created by stevijo on 04.10.16.
//

#include "Github.h"
#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string,std::vector<std::string>> channelMap{};

bool Github::userOwnsChannel(const std::string &channel) {
    using namespace rapidjson;

    auto channels = channelMap.find(uid);
    if(channels != end(channelMap)) {
        auto pos = find(begin(channels->second),end(channels->second),channel);
        if(pos != end(channels->second)) {
            return true;
        }
    } else {
        auto it = channelMap.insert(std::pair<std::string,std::vector<std::string>>(uid, std::vector<std::string>()));
        channels = it.first;
    }

    updateCache(channels->second);

    auto pos = find(begin(channels->second),end(channels->second),channel);
    return pos != end(channels->second);
}



void Github::updateCache(std::vector<std::string>& channels) {
    using namespace rapidjson;


    auto result = cpr::Get(cpr::Url{"https://api.github.com/user"},
                           cpr::Parameters{{"access_token",token}});
    Document userData;
    userData.Parse(result.text.c_str());
    result = cpr::Get(cpr::Url{userData["repos_url"].GetString()},cpr::Parameters{{"access_token", token}});

    Document repos;
    repos.Parse(result.text.c_str());

    auto repoArray = repos.GetArray();
    for(auto& value:repoArray) {
        channels.push_back(value.GetObject()["full_name"].GetString());
    }

    result = cpr::Get(cpr::Url{userData["organizations_url"].GetString()},cpr::Parameters{{"access_token", token}});
    Document orgs;
    orgs.Parse(result.text.c_str());

    for(auto& value:orgs.GetArray()) {
        result = cpr::Get(cpr::Url{value.GetObject()["repos_url"].GetString()},cpr::Parameters{{"access_token", token}});
        Document org;
        org.Parse(result.text.c_str());
        for(auto& repo:org.GetArray()) {
            channels.push_back(repo.GetObject()["full_name"].GetString());
        }
    }


}

void Github::updateCache() {
    auto channels = channelMap.find(uid);
    if(channels != end(channelMap)) {
        channels->second = std::vector<std::string>();
    } else {
        auto it = channelMap.insert(std::pair<std::string,std::vector<std::string>>(uid, std::vector<std::string>()));
        channels = it.first;
    }

    updateCache(channels->second);
}
