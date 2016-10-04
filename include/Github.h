//
// Created by stevijo on 04.10.16.
//

#ifndef LIVEPLAYLIST_GITHUB_H
#define LIVEPLAYLIST_GITHUB_H

#include <string>
#include <vector>
#include <map>

class Github {
public:
    Github(const std::string& token) : token(token) {}
    bool userOwnsChannel(const std::string& channel);
private:
    std::string token;
};


#endif //LIVEPLAYLIST_GITHUB_H
