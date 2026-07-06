//
// Created by Sakchham Sangroula on 6/28/26.
//

#include "threadManager.hpp"
#include "queue.hpp"

threadManager::threadManager(int maxSize) : workQueue(maxSize) {
    threads = std::vector<std::thread>(maxSize);
}

void threadManager::submit(std::function<void()> task) {
    std::unique_lock threadPoolLock(threadLock);
    if (threads.size() < maxSize && workQueue.size() > 0) {
        std::function<void()> work = workQueue.pop();
        threads.emplace_back(work);
    } else if (threads.size() < maxSize && workQueue.size() == 0) {
        threads.emplace_back(task);
    }
}

// taskA created-> put in threads.
// done until task maxSize.
// more tasks are put in Queue.
// these tasks should be worked on by a conditional variable.