//
// Created by PC on 7/6/2026.
//

#include "linkedListNum.hpp"

linkedListNum::linkedListNum() : head(nullptr) {}
void linkedListNum::put(int value) {
    std::unique_lock dataAccessLock(lock);
    numNode *newNode = new numNode{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        dataAccessLock.unlock();
        return;
    }
    auto curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
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
        dataAccessLock.unlock();
        return;
    }
    if (prev == nullptr) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;
    dataAccessLock.unlock();
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