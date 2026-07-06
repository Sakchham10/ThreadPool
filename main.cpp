#include "linkedList.hpp"
#include "threadManager.hpp"

int main() {
    threadManager manager = threadManager(20);
    linkedList list = linkedList();
}

// linkedList will take the threadManger and use the threads there?
// each object will take from a pool of threadManger.
//