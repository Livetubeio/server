#include <iostream>
#include <endpoint.h>
#include <glog/logging.h>
#include "Router.h"

int main(int argc, char **argv) {
    Net::Address addr(Net::Ipv4::any(), Net::Port(9080));
    google::InitGoogleLogging(argv[0]);

    Router router(addr);
    router.init(6);
    router.start();

    router.shutdown();
    return 0;
}