#include "queue.hpp"

queue::queue(int size) : maxSize(size) {}

void queue::put(std::function<void()> *func) { taskList.append(func); }

std::function<void()> *queue::pop() {
    std::function<void()> *func = taskList.pop();
    return func;
}

int queue::getSize() { return taskList.getSize(); }

int queue::getMaxSize() { return maxSize; }