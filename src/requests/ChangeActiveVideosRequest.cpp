//
// Created by stevijo on 01.10.16.
//

#include "requests/ChangeActiveVideosRequest.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <cpr/cpr.h>
#include <sstream>

void ChangeActiveVideosRequest::execute(){

    using namespace rapidjson;

    std::stringstream ss;
    ss << ChangeActiveVideosRequest::url << this->channel << ".json";

    Document document;
    document.SetObject();

    Value active;
    active.SetString(StringRef(this->ytid.c_str()));
    document.AddMember(StringRef("active"), active, document.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    auto r = cpr::Patch(cpr::Url{ss.str()},cpr::Body{buffer.GetString()});
    std::cout << r.status_code << std::endl;
}
