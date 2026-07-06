#include "queue.hpp"

queue::queue(int maxSize) {
	this->maxSize = maxSize;
}

void queue::put(std::function<void()> func) {
	std::unique_lock queueAccessLock(queueLock);
	if (this->taskList.getSize() >= maxSize) {
		queueFull.wait(queueAccessLock, [this] { return this->taskList.getSize() < this->maxSize; });
	}
	taskList.append(func);
	queueAccessLock.release();
}

std::function<void()> queue::pop() {
	std::unique_lock queueAccessLock(queueLock);
	if (this->taskList.getSize() > 0) {
		queueFull.wait(queueAccessLock, [this] { return this->taskList.getSize() > 0; });
	}
	std::function<void()> func = taskList.pop();
	queueAccessLock.release();
	return func;
}