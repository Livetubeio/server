//
// Created by stevijo on 04.10.16.
//

#include "jwt/TokenVerifier.h"
#include "helper.h"
#include "jwt/CertificatesStore.h"
#include <rapidjson/document.h>
#include <ctime>

bool TokenVerifier::verify() {
    using namespace rapidjson;

    auto pos = token.token.find('.');
    if(pos == std::string::npos) {
        return false;
    }
    auto basic = token.token.substr(0,pos);

    auto decoded = H::base64decode(basic);

    Document header;
    header.Parse(decoded.c_str());
    if(!header.HasMember("kid")) {
        return false;
    }
    std::string key = header["kid"].GetString();

    auto& certificates = CertificatesStore::instance();
    if(!certificates.hasCertificate(key)) {
        return false;
    }

    auto pubKey = certificates.getCertificate(key).getPubKey();

    auto& jwt_token = token.jwt_token;

    auto res = jwt_decode(&jwt_token,token.token.c_str(),
                          reinterpret_cast<const unsigned char*>(pubKey.c_str()),
                          static_cast<int>(pubKey.size()));

    if(res > 0) {
        std::cout << "no valid pubkey" << std::endl;
        return false;
    }

    auto currentTime = std::time(0);

    static const std::string projectId = "livetubeio-16323";
    static const std::string issuer = "https://securetoken.google.com/livetubeio-16323";

    auto exp = std::stoi(jwt_get_grant(jwt_token,"exp"));
    auto iat = std::stoi(jwt_get_grant(jwt_token,"iat"));
    auto aud = std::string(jwt_get_grant(jwt_token,"aud"));
    auto iss = std::string(jwt_get_grant(jwt_token,"iss"));
    auto sub = std::string(jwt_get_grant(jwt_token,"sub"));

    if(exp <= currentTime) {
        std::cout << "expired" << std::endl;
        jwt_free(jwt_token);
        jwt_token = NULL;
        return false;
    }

    if(iat >= currentTime) {
        jwt_free(jwt_token);
        jwt_token = NULL;
        return false;
    }

    if(aud != projectId) {
        jwt_free(jwt_token);
        jwt_token = NULL;
        return false;
    }

    if(iss != issuer) {
        jwt_free(jwt_token);
        jwt_token = NULL;
        return false;
    }

    if(sub.empty()) {
        jwt_free(jwt_token);
        jwt_token = NULL;
        return false;
    }

    return true;
}
