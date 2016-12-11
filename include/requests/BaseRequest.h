#ifndef LIVEPLAYLIST_BASEREQUEST_H
#define LIVEPLAYLIST_BASEREQUEST_H

#include "ThreadPool.h"

/**
 * Base class for request which also handles asynchronous
 * execution of a server initiated request
 *
 */
class BaseRequest {
public:
    void join();
    void executeAsync();
protected:
    virtual void execute() = 0;
    ThreadPool threadPool;
};


#endif
