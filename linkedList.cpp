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
    size--;
    if (head == tail && head != nullptr) {
        std::cout << "Only one node: popping from head\n";
        std::function<void()> *func = head->value;
        delete (head);
        head = nullptr;
        tail = nullptr;
        return func;
    }
    if (head == tail && head == nullptr) {
        std::cout << "No node to pop:\n";
        size = 0;
        return nullptr;
    }
    node *currTail = tail;
    currTail->prev->next = nullptr;
    tail = currTail->prev;
    std::function<void()> *func = currTail->value;
    delete (currTail);
    return func;
}

int linkedList::getSize() { return size; }

linkedList::linkedList():head(nullptr),tail(nullptr),size(0){
}

linkedList::~linkedList() {
    while (head != nullptr) {
        node *temp = head;
        head = temp->next;
        delete temp->value;
        delete temp;
    }
}