//
// Created by Sakchham Sangroula on 6/28/26.
//

#include "threadManager.hpp"
#include "queue.hpp"

threadManager::threadManager(int threadCount) : threadCount(threadCount) {
    threads.reserve(threadCount);
    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back(&threadManager::threadTask, this);
    }
}

void threadManager::submit(std::function<void()> *task) {
    std::unique_lock queueDataLock(queueLock);
    if (shuttingDown) {
        delete task;
        throw std::runtime_error("submit after shutdown");
    }
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

threadManager::~threadManager() = default;

int threadManager::getQueueSize() {
    std::unique_lock queueDataLock(queueLock);
    const int size = workQueue.size();
    queueDataLock.unlock();
    return size;
}

void threadManager::shutDown() {
    std::unique_lock queueDataLock(queueLock);
    shuttingDown = true;
    queueDataLock.unlock();
    taskInQueue.notify_all();
    for (auto &thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}