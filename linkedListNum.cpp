//
// Created by PC on 7/6/2026.
//

#include "linkedListNum.hpp"

#include <iostream>

#include "utils.hpp"

linkedListNum::linkedListNum(threadManager &thrdMngr) : head(nullptr), manager(thrdMngr) {}
void linkedListNum::put(int value) {
    std::unique_lock dataAccessLock(lock);
    numNode *newNode = new numNode{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        std::cout << "Adding to head: " << value << "\n";
        dataAccessLock.unlock();
        return;
    }
    auto curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
    std::cout << "Adding: " << value << "\n";
    dataAccessLock.unlock();
}

void linkedListNum::findAndpop(int value) {
    std::unique_lock dataAccessLock(lock);
    auto curr = head;
    numNode *prev = nullptr;
    while (curr && curr->value != value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == nullptr) {

        std::cout << "Nothing to pop\n";
        dataAccessLock.unlock();
        return;
    }
    if (prev == nullptr) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;
    std::cout << "Remove value: " << value << "\n";
    dataAccessLock.unlock();
}
int linkedListNum::tests(int time) {
    auto start = std::chrono::steady_clock::now();
    while (true) {
        auto randVal = utils::getRandom(0, 2);
        if (randVal == 0) {
            manager.submit(new std::function([this]() { this->findAndpop(utils::getRandom(1, 100)); }));
        } else {
            manager.submit(new std::function([this]() { this->put(utils::getRandom(1, 100)); }));
        }
        totalTasks++;
        auto end = std::chrono::steady_clock::now();
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (elapsedMs > time) {
            int val = manager.getQueueSize();
            std::cout << "Total remaining now: " << val << "\n";
            return totalTasks;
        }
    }
}

linkedListNum::~linkedListNum() {
    std::unique_lock dataAccessLock(lock);
    while (head != nullptr) {
        numNode *temp = head;
        head = head->next;
        delete temp;
    }
    dataAccessLock.unlock();
}