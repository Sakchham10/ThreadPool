#include "linkedList.hpp"

#include <iostream>

#include "threadManager.hpp"

void linkedList::append(std::function<void()> *value) {
    node *newNode = new node{value, nullptr, nullptr};
    size++;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    node *currTail = tail;
    currTail->next = newNode;
    newNode->prev = currTail;
    tail = newNode;
}

std::function<void()> *linkedList::pop() {
    if (head == nullptr) {
        return nullptr;
    }
    size--;
    if (head == tail && head != nullptr) {
        std::function<void()> *func = head->value;
        delete (head);
        head = nullptr;
        tail = nullptr;
        return func;
    }
    if (head == tail && head == nullptr) {
        size = 0;
        return nullptr;
    }
    node *currHead = head;
    head = currHead->next;
    head->prev = nullptr;
    std::function<void()> *func = currHead->value;
    delete (currHead);
    return func;
}

int linkedList::getSize() { return size; }

linkedList::linkedList() : head(nullptr), tail(nullptr), size(0) {}

linkedList::~linkedList() {
    while (head != nullptr) {
        node *temp = head;
        head = temp->next;
        delete temp->value;
        delete temp;
    }
}