//
// Created by stevijo on 03.10.16.
//

#ifndef LIVEPLAYLIST_CERTIFICATES_H
#define LIVEPLAYLIST_CERTIFICATES_H

#include "jwt/Certificate.h"
#include <string>
#include <map>
#include <mutex>
#include <atomic>
#include <condition_variable>

class Certificates {
public:
    static Certificates& instance() {
        static Certificates certificates;
        return certificates;
    }
    bool hasCertificate(const std::string& keyId);
    Certificate& getCertificate(const std::string& keyId);
private:
    std::atomic<bool> writingData{};
    std::condition_variable cv;
    std::mutex mutex;
    std::map<std::string,Certificate> certificates;
};


#endif //LIVEPLAYLIST_CERTIFICATE_H
