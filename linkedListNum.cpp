//
// Created by PC on 7/6/2026.
//

#include "linkedListNum.hpp"

#include <iostream>

#include "utils.hpp"

linkedListNum::linkedListNum() : head(nullptr), totalTasks(0) {}
void linkedListNum::put(int value) {
    std::unique_lock dataAccessLock(lock);
    auto *newNode = new numNode{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        dataAccessLock.unlock();
        std::cout << "Adding to head: " << value << "\n";
        return;
    }
    auto curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
    dataAccessLock.unlock();
    totalTasks++;
    std::cout << "Adding: " << value << "\n";
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
        dataAccessLock.unlock();
        std::cout << "Nothing to pop\n";
        return;
    }
    if (prev == nullptr) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;
    dataAccessLock.unlock();
    totalTasks++;
    std::cout << "Remove value: " << value << "\n";
}
void linkedListNum::test(threadManager &manager, int time) {
    auto start = std::chrono::steady_clock::now();
    while (true) {
        auto randVal = utils::getRandom(0, 2);
        if (randVal == 0) {
            manager.submit(new std::function([this]() { this->findAndpop(utils::getRandom(1, 100)); }));

        } else {
            manager.submit(new std::function([this]() { this->put(utils::getRandom(1, 100)); }));
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (elapsedMs > time) {
            totalTimeTaken = elapsedMs;
            return;
        }
    }
}

void linkedListNum::getStats() {
    std::cout << "Total tasks: " << totalTasks << "\n";
    std::cout << "Total time taken : " << totalTimeTaken << "\n";
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