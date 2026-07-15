# Thread-Safe Data Structures in C++

This is a small C++20 learning project for experimenting with thread
coordination and manually implemented data structures.

The program currently builds a fixed-size worker pool, submits randomized linked
list operations into it for a short stress run, shuts the workers down, and
prints basic task statistics.

## What Is In This Repo

- `threadManager`: a simple thread pool. It owns worker threads, accepts
  heap-allocated `std::function<void()>` tasks, blocks submissions when the
  queue reaches its max size, and drains queued work during shutdown.
- `queue`: a bounded task queue facade used by `threadManager`.
- `linkedList`: a doubly linked list that stores task pointers for the queue.
- `linkedListNum`: a singly linked integer list used as the concurrency test
  target. Writers use a mutex; readers use a basic readers-writer pattern with a
  `std::binary_semaphore`, a reader count, and the same writer mutex.
- `utils`: a random integer helper used by the stress test.
- `main.cpp`: creates a `threadManager` with one worker, runs the integer-list
  stress test for about 4000 ms, shuts the pool down, and prints stats.

## Current Behavior

The stress test repeatedly submits random insert or remove tasks against values
from 1 to 100. Each completed list operation increments a task counter. At the
end, the program prints:

- total completed tasks
- elapsed stress-test time in milliseconds

The list methods also print individual add/remove/miss messages while the test
runs, so normal output is intentionally noisy.

## Requirements

- A C++20-compatible compiler
- CMake, if you want to use the included `CMakeLists.txt`

## Build and Run

Using a compiler directly:

```sh
clang++ -std=c++20 main.cpp linkedList.cpp queue.cpp threadManager.cpp utils.cpp linkedListNum.cpp -o ThreadSafeDataStructure
./ThreadSafeDataStructure
```

Using CMake:

```sh
cmake -S . -B build
cmake --build build
./build/ThreadSafeDataStructure
```

## Notes From The Current Implementation

- Task ownership is manual: callers submit `new std::function<void()>`, and the
  thread pool deletes each task after execution or after rejected submission.
- `queue` and `linkedList` are not independently thread-safe. They are protected
  by `threadManager`'s queue mutex.
- `linkedListNum` uses coarse-grained write locking and a simple readers-writer
  scheme. This keeps the code approachable, but it is still experimental.
- `threadManager::restart()` is declared in the header but is not implemented.
- There are no automated tests yet; `main.cpp` is the current executable demo.