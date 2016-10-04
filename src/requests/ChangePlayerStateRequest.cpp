//
// Created by stevijo on 01.10.16.
//

#include "requests/ChangePlayerStateRequest.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <cpr/cpr.h>

void ChangePlayerStateRequest::execute() {
    using namespace rapidjson;

    std::stringstream ss;
    ss << ChangePlayerStateRequest::url << this->channel << ".json";

    Document document;
    document.SetObject();

    Value value;
    value.SetInt(static_cast<int>(this->state));
    document.AddMember(StringRef("playerstate"), value, document.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    auto r = cpr::Patch(cpr::Url{ss.str()},cpr::Body{buffer.GetString()});
    std::cout << r.status_code << std::endl;
}

