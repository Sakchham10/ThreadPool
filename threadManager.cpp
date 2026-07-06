//
// Created by Sakchham Sangroula on 6/28/26.
//

#include "threadManager.hpp"
#include "queue.hpp"

threadManager::threadManager(int maxSize) {
    threads.reserve(maxSize);
    for (int i = 0; i < maxSize; i++) {
        threads.emplace_back(&threadManager::threadTask, this);
    }
}

void threadManager::submit(std::function<void()> *task) {
    std::unique_lock queueDataLock(queueLock);
    this->workQueue.put(task);
    queueDataLock.unlock();
    taskInQueue.notify_one();
}


void threadManager::threadTask() {
    // look at cleanup, because currently if the shuttingDown is changed to true, none of the threads will pick up the
    // remaining work and will finish.
    while (!shuttingDown) {
        std::unique_lock queueDataLock(queueLock);
        taskInQueue.wait(queueDataLock, [this]() { return this->workQueue.size() > 0; });
        std::function<void()> *task = this->workQueue.pop();
        queueDataLock.unlock();
        (*task)();
        delete task;
    }
}