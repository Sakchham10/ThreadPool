#include "linkedList.hpp"

#include <iostream>

#include "threadManager.hpp"

void linkedList::append(std::function<void()> value) {
    writerSemaphore.acquire();
    node *newNode = new node{std::move(value), nullptr, nullptr};
    size++;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        writerSemaphore.release();
        return;
    }
    node *currTail = tail;
    currTail->next = newNode;
    newNode->prev = currTail;
    tail = newNode;
    writerSemaphore.release();
}

std::function<void()> linkedList::pop() {
    writerSemaphore.acquire();
    size--;
    if (head == tail && head != nullptr) {
        std::cout << "Only one node: popping from head\n";
        std::function<void()> func = head->value;
        delete(head);
        head = nullptr;
        tail = nullptr;
        writerSemaphore.release();
        return func;
    }
    if (head == tail && head == nullptr) {
        std::cout << "No node to pop:\n";
        writerSemaphore.release();
        return nullptr;
    }
    node *currTail = tail;
    currTail->prev->next = nullptr;
    tail = currTail->prev;
    std::function<void()> func = currTail->value;
    delete(currTail);
    writerSemaphore.release();
    return func;
}

int linkedList::getSize() {
    return size;
}

linkedList::linkedList() : readerSemaphore(1), writerSemaphore(1) {
    head = nullptr;
}

linkedList::~linkedList() {
    while (head != nullptr) {
        node *temp = head;
        head = temp->next;
        delete temp;
    }
}