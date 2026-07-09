#include <iostream>


#include "linkedList.hpp"
#include "linkedListNum.hpp"
#include "threadManager.hpp"

int main() {
    threadManager manager = threadManager(40);
    linkedListNum myList = linkedListNum(manager);
    std::cout << myList.tests(100) << " :tasks completed\n";
    manager.waitForAll();
}