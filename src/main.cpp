#include <iostream>
#include <endpoint.h>
#include <glog/logging.h>
#include "helper.h"
#include "Router.h"

int main(int argc, char **argv) {
    Net::Address addr("127.0.0.1", Net::Port(9080));
    google::InitGoogleLogging(argv[0]);

    Router router(addr);
    router.init();
    router.start();

    router.shutdown();
    return 0;
}