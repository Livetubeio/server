#include <string>
#include <iostream>
#include <googleapis/util/status.h>
#include <googleapis/client/data/data_reader.h>
#include <googleapis/client/transport/http_request.h>
#include <APICredential.h>
#include <cstdlib>

using namespace googleapis;
using client::DataReader;
using client::HttpRequest;

APICredential::APICredential() {
    auto path = std::getenv("API_KEY");
    if(path == NULL) return;
    key = path;
}

const std::string APICredential::type() const {
    return "Api";
}

util::Status APICredential::Refresh() {
    return client::StatusOk();
}

util::Status APICredential::Load(DataReader *serialized_credential) {
    return client::StatusOk();
}

DataReader* APICredential::MakeDataReader() const {
    return nullptr;
}

util::Status APICredential::AuthorizeRequest(HttpRequest* request) {
    if(key.empty()) {
        return client::StatusInternalError("API_KEY not set");
    }
    std::stringstream ss;
    ss << request->url() << "&key=" << key;
    request->set_url(ss.str());
    return client::StatusOk();
}

void APICredential::RefreshAsync(Callback1<util::Status> *callback) {
    callback->Run(client::StatusOk());
}


