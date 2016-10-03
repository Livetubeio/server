//
// Created by stevijo on 03.10.16.
//

#include "jwt/Certificates.h"
#include "jwt/Certificate.h"
#include <algorithm>
#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <json/value.h>
#include <iostream>

bool Certificates::hasCertificate(const std::string &keyId) {
    using namespace rapidjson;

    bool result = certificates.find(keyId) != certificates.end();
    if(result) return true;

    std::cout << "get certificates from google" << std::endl;
    auto r = cpr::Get(cpr::Url{"https://www.googleapis.com/robot/v1/metadata/x509/securetoken@system.gserviceaccount.com"});
    Document document;
    document.Parse(r.text.c_str());

    std::lock_guard<std::mutex> lock(mutex);
    writingData = true;
    for_each(document.MemberBegin(),document.MemberEnd(),[&](GenericMember<UTF8<>,MemoryPoolAllocator<>>& value) {
        certificates[value.name.GetString()] = Certificate(value.value.GetString());
    });
    writingData = false;
    cv.notify_all();
    return certificates.find(keyId) != certificates.end();
}

Certificate& Certificates::getCertificate(const std::string &keyId) {

    std::unique_lock<std::mutex> lock(mutex);
    if(writingData) {
        cv.wait(lock);
    }
    return certificates[keyId];
}
