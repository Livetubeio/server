//
// Created by stevijo on 05.10.16.
//

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <cpr/cpr.h>
#include <sstream>
#include "requests/UpdateChannelRequest.h"

void UpdateChannelRequest::execute() {
    using namespace rapidjson;

    std::stringstream ss;
    ss << UpdateChannelRequest::url << this->channel << ".json";

    Document document;
    document.SetObject();

    if(this->hasState) {
        Value value;
        value.SetInt(static_cast<int>(this->state));
        document.AddMember(StringRef("playerstate"), value, document.GetAllocator());
    }
    if(this->hasActive) {
        Value active;
        active.SetString(StringRef(this->active.c_str()));
        document.AddMember(StringRef("active"), active, document.GetAllocator());
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    auto r = cpr::Patch(cpr::Url{ss.str()},cpr::Body{buffer.GetString()});
    std::cout << r.status_code << std::endl;
}

void UpdateChannelRequest::setState(const UpdateChannelRequest::State &state) {
    hasState = true;
    this->state = state;
}

void UpdateChannelRequest::setActive(const std::string &active) {
    hasActive = true;
    this->active = active;
}
