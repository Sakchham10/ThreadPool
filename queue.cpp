#include "queue.hpp"

queue::queue() {}

void queue::put(std::function<void()> *func) { taskList.append(func); }

std::function<void()> *queue::pop() {
    std::function<void()> *func = taskList.pop();
    return func;
}

int queue::size() { return taskList.getSize(); }