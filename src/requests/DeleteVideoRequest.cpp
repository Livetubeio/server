#include <iosfwd>
#include <sstream>
#include <cpr/cpr.h>
#include "requests/DeleteVideoRequest.h"

void DeleteVideoRequest::execute() {

    std::stringstream ss;
    ss << DeleteVideoRequest::url << channel << "/videos/" << video << ".json";

    cpr::Delete(cpr::Url{ss.str()});
}
