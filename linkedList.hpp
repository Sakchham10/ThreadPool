#ifndef THREADSAFEDATASTRUCTURE_LINKEDLIST_HPP
#define THREADSAFEDATASTRUCTURE_LINKEDLIST_HPP
#include <semaphore>
#include "threadManager.hpp"


struct node {
   std::function<void()> value;
   node *next;
   node *prev;
};

class linkedList {
public:
   void init(int startRange, int endRange);

   linkedList();

   ~linkedList();

   int getSize();

   void append(std::function<void()> func);

   std::function<void()> pop();

private:
   node *head;
   node *tail;
   std::binary_semaphore readerSemaphore;
   std::binary_semaphore writerSemaphore;
   int size;
   int totalTimeToRun;
};
#endif