#include "linkedList.hpp"
#include "threadManager.hpp"

int main() {
    threadManager manager = threadManager(20);
    queue myQueue = queue();
    // std::function task = [&myQueue]() { myQueue.pop(); };
    // manager.submit(&task);
}