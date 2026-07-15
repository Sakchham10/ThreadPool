//
// Created by Sakchham Sangroula on 6/28/26.
//

#ifndef THREADSAFEDATASTRUCTURE_THREADMANAGER_HPP
#define THREADSAFEDATASTRUCTURE_THREADMANAGER_HPP
#include <condition_variable>
#include <thread>
#include <vector>
#include "queue.hpp"

class threadManager {
    int threadCount;
    std::condition_variable taskInQueue;
    std::mutex queueLock;
    std::vector<std::thread> threads;
    queue workQueue;
    bool shuttingDown = false;
    void threadTask();

public:
    std::mutex threadLock;

    std::condition_variable cv;

    explicit threadManager(int threadCount = 10);
    ~threadManager();

    void submit(std::function<void()> *task);
    int getQueueSize();
    void shutDown();
    void restart();
};


#endif // THREADSAFEDATASTRUCTURE_THREADMANAGER_HPP