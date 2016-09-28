#include <iostream>
#include <pistache/endpoint.h>
#include "Router.h"

int main() {
    Net::Address addr(Net::Ipv4::any(), Net::Port(9080));

    Router router(addr);
    router.init(2);
    router.start();

    router.shutdown();
    return 0;
}