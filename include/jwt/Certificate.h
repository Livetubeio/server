#ifndef LIVEPLAYLIST_CERTIFICATE_H
#define LIVEPLAYLIST_CERTIFICATE_H

#include <string>

/**
 * Wrapperclass for certificate
 */
class Certificate {
public:
    Certificate() {}
    Certificate(const std::string& certificate) : certificate(certificate) { }
    std::string getPubKey();
private:
    std::string certificate;
};

#endif
