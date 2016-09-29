//
// Created by stevijo on 29.09.16.
//

#ifndef LIVEPLAYLIST_APICREDENTIAL_H
#define LIVEPLAYLIST_APICREDENTIAL_H

#include <googleapis/client/transport/http_authorization.h>
#include <googleapis/client/data/data_reader.h>
#include <googleapis/client/transport/http_request.h>

using namespace googleapis;
using client::AuthorizationCredential;
using client::DataReader;
using client::HttpRequest;

class APICredential : public AuthorizationCredential {
public:
    APICredential(const std::string& key) : key(key) {}
    const std::string type() const;
    util::Status Refresh();
    void RefreshAsync(Callback1<util::Status>* callback);
    util::Status Load(DataReader *serialized_credential);
    DataReader* MakeDataReader() const;
    util::Status AuthorizeRequest(HttpRequest* request);

private:
    std::string key;
};


#endif //LIVEPLAYLIST_APICREDENTIAL_H
