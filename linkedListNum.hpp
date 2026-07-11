//
// Created by PC on 7/6/2026.
//

#ifndef THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP
#define THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP
#include <mutex>

#include "threadManager.hpp"


struct numNode {
    int value;
    numNode *next;
};
class linkedListNum {
    std::mutex lock;
    numNode *head;
    int totalTasks;

public:
    void put(int value);
    void findAndpop(int value);
    int tests(threadManager &thrdMngr, int time);
    linkedListNum();
    ~linkedListNum();
};


#endif // THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP