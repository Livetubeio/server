#ifndef LIVEPLAYLIST_GITHUB_H
#define LIVEPLAYLIST_GITHUB_H

#include <string>
#include <vector>
#include <map>

class GithubService {
public:
    GithubService(const std::string& token, const std::string& uid) : token(token), uid(uid) {}
    void updateCache();
    void updateCache(std::vector<std::string>& channels);
    bool userOwnsChannel(const std::string& channel);
private:
    std::string token;
    std::string uid;
};


#endif
