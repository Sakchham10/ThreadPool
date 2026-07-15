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
    long long totalTimeTaken;

public:
    void put(int value);
    void findAndpop(int value);
    void test(threadManager &thrdMngr, int time);
    void getStats();
    linkedListNum();
    ~linkedListNum();
};


#endif // THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP