//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "header/AccessControlAllowOrigin.h"
#include "header/AccessControlAllowMethods.h"
#include "header/AccessControlMaxAge.h"
#include "header/AccessControlAllowHeaders.h"
#include <algorithm>
#include <openssl/pem.h>


using namespace std;

namespace H {

    vector<string> split(const string stri, char c = ' ') {
        auto str = stri.c_str();
        vector<string> result;

        do {
            const char *begin = str;

            while (*str != c && *str)
                str++;

            result.push_back(string(begin, str));
        } while (0 != *str++);

        return result;
    }

    map<string, string> parseRequest(const Net::Rest::Request &request) {
        map<string, string> params;

        auto fields = split(request.body(), '&');
        for (auto param:fields) {
            auto keyValue = split(param, '=');

            params.insert(std::pair<std::string, std::string>(keyValue[0], keyValue[1]));
        }
        return params;
    }

    std::string base64decode(std::string string) {

        // Replace b64 strings
        for_each(begin(string),end(string),[](char& c) {
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
        auto offset = 4 - (string.size() % 4);
        if(offset < 4) {
            for(unsigned i=offset;i>0;i--) {
                string.append("=");
            }
        }

        BIO *bmem,*b64;
        bmem = BIO_new_mem_buf(string.c_str(),static_cast<int>(string.size()));
        b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO_push(b64, bmem);
        auto len = BIO_pending(b64);
        char decodedC[len];
        len = BIO_read(b64, decodedC, len);
        std::string decoded(decodedC,len);
        BIO_free_all(b64);

        return decoded;
    }

    void addCorsHeaders(Net::Http::ResponseWriter& response) {
        response.headers().add(
                std::make_shared<AccessControlAllowOrigin>(
                        std::initializer_list<std::string>{"*"})
        );
        response.headers().add(
                std::make_shared<AccessControlAllowMethods>(
                        std::initializer_list<std::string>{"GET","POST","PUT","DELETE"}
                )
        );
        response.headers().add(
                std::make_shared<AccessControlMaxAge>(2629744)
        );
        response.headers().add(
                std::make_shared<AccessControlAllowHeaders>(
                        std::initializer_list<std::string>{"X-LIVETUBE-AUTH","X-GITHUB-AUTH"}
                )
        );
    }

}