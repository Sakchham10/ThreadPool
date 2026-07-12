//
// Created by Sakchham Sangroula on 6/28/26.
//

#ifndef THREADSAFEDATASTRUCTURE_QUEUE_HPP
#define THREADSAFEDATASTRUCTURE_QUEUE_HPP
#include <functional>
#include "linkedList.hpp"


class queue {
    int maxSize;
    linkedList taskList;

public:
    void put(std::function<void()> *func);

    std::function<void()> *pop();

    int getSize();
    int getMaxSize();

    queue(int size = 10);
};

#endif // THREADSAFEDATASTRUCTURE_QUEUE_HPP