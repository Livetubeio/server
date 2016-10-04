//
// Created by stevijo on 01.10.16.
//

#ifndef LIVEPLAYLIST_BASEREQUEST_H
#define LIVEPLAYLIST_BASEREQUEST_H

#include "ThreadPool.h"

class BaseRequest {
public:
    void join();
    void executeAsync();
protected:
    virtual void execute() = 0;
    ThreadPool threadPool;
};


#endif //LIVEPLAYLIST_BASEREQUEST_H
