#include <iostream>
#include "linkedListNum.hpp"
#include "threadManager.hpp"

int main() {
    threadManager manager = threadManager(1);
    linkedListNum myList = linkedListNum();
    myList.test(manager, 4000);
    manager.shutDown();
    myList.getStats();
    threadManager manager2 = threadManager(10);
    linkedListNum myList2 = linkedListNum();
    myList2.test(manager, 4000);
    myList.getStats();
}