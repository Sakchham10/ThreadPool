#ifndef THREADSAFEDATASTRUCTURE_LINKEDLIST_HPP
#define THREADSAFEDATASTRUCTURE_LINKEDLIST_HPP
#include <functional>

struct node {
    std::function<void()> *value;
    node *next;
    node *prev;
};

class linkedList {
public:
    linkedList();

    ~linkedList();

    int getSize();

    void append(std::function<void()> *func);

    std::function<void()> *pop();

private:
    node *head;
    node *tail;
    int size;
};
#endif