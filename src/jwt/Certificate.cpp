//
// Created by stevijo on 03.10.16.
//

#include "jwt/Certificate.h"
#include <openssl/pem.h>

std::string Certificate::getPubKey() {
    BIO *bio, *write;
    X509* cert;
    EVP_PKEY* pkey;
    write = BIO_new(BIO_s_mem());
    bio = BIO_new_mem_buf(certificate.c_str(),static_cast<int>(certificate.size()));

    cert = PEM_read_bio_X509(bio,0,0,0);
    if(!cert) {
        return "";
    }
    pkey = X509_get_pubkey(cert);
    if(!pkey) {
        return "";
    }
    PEM_write_bio_PUBKEY(write,pkey);
    char* result;
    auto len = BIO_get_mem_data(write, &result);
    std::string res(result, len);
    EVP_PKEY_free(pkey);
    X509_free(cert);
    BIO_free_all(bio);
    BIO_free_all(write);

    return res;
}
