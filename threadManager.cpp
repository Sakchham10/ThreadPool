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
    while (true) {
        std::unique_lock queueDataLock(queueLock);
        taskInQueue.wait(queueDataLock, [this]() { return shuttingDown || this->workQueue.size() > 0; });
        if (shuttingDown && this->workQueue.size() == 0) {
            return;
        }
        std::function<void()> *task = this->workQueue.pop();
        queueDataLock.unlock();
        (*task)();
        delete task;
    }
}

threadManager::~threadManager() {
    std::unique_lock queueDataLock(queueLock);
    shuttingDown = true;
    queueDataLock.unlock();
    taskInQueue.notify_all();
}


void threadManager::waitForAll() {
    for (auto &thread: threads) {
        thread.join();
    }
}

int threadManager::getQueueSize() { return workQueue.size(); }