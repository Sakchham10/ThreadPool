#include "linkedList.hpp"
#include "threadManager.hpp"

int main() {
	threadManager manager = threadManager(20);
	linkedList list = linkedList();
	threadManager.run(linkedList.pop(22));
	threadManager.run(linkedList.push(11));
	threadManager.run(linkedList.pop(17))
}

//linkedList will take the threadManger and use the threads there?
//each object will take from a pool of threadManger.
//