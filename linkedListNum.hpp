//
// Created by PC on 7/6/2026.
//

#ifndef THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP
#define THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP
#include <mutex>


struct numNode {
    int value;
    numNode *next;
};
class linkedListNum {
    std::mutex lock;
    numNode *head;

public:
    void put(int value);
    void findAndpop(int value);
    linkedListNum();
    ~linkedListNum();
};


#endif // THREADSAFEDATASTRUCTURE_LINKEDLISTNUM_HPP