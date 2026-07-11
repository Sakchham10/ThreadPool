#include <iostream>
#include "linkedListNum.hpp"
#include "threadManager.hpp"

int main() {
    threadManager manager = threadManager(40);
    linkedListNum myList = linkedListNum();
    std::cout << myList.tests(manager, 1000) << " :tasks completed\n";
    manager.shutDown();
}