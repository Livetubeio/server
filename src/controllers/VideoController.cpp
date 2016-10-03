//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "requests/AddVideoRequest.h"
#include "controllers/VideoController.h"
#include "jwt/Certificates.h"
#include <rapidjson/document.h>
#include <memory>
#include <jwt.h>
#include <openssl/pem.h>
#include <algorithm>

using namespace googleapis;
using namespace rapidjson;

void VideoController::create(const Rest::Request &request, Net::Http::ResponseWriter response) {

    Document document;
    document.Parse(request.body().c_str());

    std::string token = document["token"].GetString();

    auto pos = token.find('.');
    if(pos == std::string::npos) {
        response.send(Http::Code::Bad_Request);
        return;
    }
    auto basic = token.substr(0,pos);
    // Replace b64 strings
    for_each(begin(basic),end(basic),[](char& c) {
        switch(c) {
            case '-':
                c = '+';
                break;
            case '_':
                c = '/';
                break;
            default:
                break;
        }
    });
    auto offset = 4 - (basic.size() % 4);
    if(offset < 4) {
        for(unsigned i=offset;i>0;i--) {
            basic.append("=");
        }
    }

    BIO *bmem,*b64;
    bmem = BIO_new_mem_buf(basic.c_str(),static_cast<int>(basic.size()));
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_push(b64, bmem);
    auto len = BIO_pending(b64);
    char decodedC[len];
    len = BIO_read(b64, decodedC, len);
    std::string decoded(decodedC,len);
    BIO_free_all(b64);

    Document header;
    header.Parse(decoded.c_str());
    std::string key = header["kid"].GetString();

    auto& certificates = Certificates::instance();
    auto res = certificates.hasCertificate(key);
    if(res) {
        std::cout << certificates.getCertificate(key).getPubKey() << std::endl;
    }
    response.send(Http::Code::Ok);
    return;
    Document body;
    body.Parse(request.body().c_str());
    if (!body.IsObject() ||
        !body.HasMember("ytid") || !body.HasMember("channel") ||
        !body["ytid"].IsString() || !body["channel"].IsString()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    AddVideoRequest videoRequest{body["channel"].GetString(),body["ytid"].GetString()};
    videoRequest.executeAsync();

    response.send(Http::Code::Ok);
}
