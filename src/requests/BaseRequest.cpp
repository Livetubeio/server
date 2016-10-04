//
// Created by stevijo on 01.10.16.
//

#include "requests/BaseRequest.h"

void BaseRequest::join() {
    threadPool.join();
}

void BaseRequest::executeAsync() {
    threadPool.executeAsync([this]() {
        this->execute();
    });
}
