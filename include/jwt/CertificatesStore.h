#ifndef LIVEPLAYLIST_CERTIFICATESSTORE_H
#define LIVEPLAYLIST_CERTIFICATESSTORE_H

#include "jwt/Certificate.h"
#include <string>
#include <map>
#include <mutex>
#include <atomic>
#include <condition_variable>

/**
 * Class responsible for holding certificates for the jwt token verification process
 */
class CertificatesStore {
public:
    static CertificatesStore& instance();
    bool hasCertificate(const std::string& keyId);
    Certificate& getCertificate(const std::string& keyId);
private:
    std::atomic<bool> writingData{};
    std::condition_variable cv;
    std::mutex mutex;
    std::map<std::string,Certificate> certificates;
};


#endif //LIVEPLAYLIST_CERTIFICATE_H
