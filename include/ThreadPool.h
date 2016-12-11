#ifndef LIVEPLAYLIST_THREADPOOL_H
#define LIVEPLAYLIST_THREADPOOL_H

#include <thread>
#include <vector>
#include <iostream>

class ThreadPool {
public:
    ThreadPool() {}
    void join() {
        for(auto& thread:threads) {
            thread.join();
        }
    }
    template<typename T>
    void executeAsync(T&& function) {
        threads.push_back(std::thread(function));
    }
private:
    std::vector<std::thread> threads;
};

#endif
