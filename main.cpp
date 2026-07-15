#include <iostream>
#include "linkedListNum.hpp"
#include "threadManager.hpp"

int main() {
    threadManager manager = threadManager(1);
    linkedListNum myList = linkedListNum();
    try {
        myList.test(manager, 4000);
        manager.shutDown();
    } catch (std::runtime_error &e) {
        manager.shutDown();
    }
    myList.getStats();
    threadManager manager2 = threadManager(10);
    linkedListNum myList2 = linkedListNum();
    myList2.test(manager2, 4000);
    manager2.shutDown();
    myList2.getStats();
}