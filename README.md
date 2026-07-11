# Thread-Safe Data Structures in C++

This repository is a learning project for building basic data structures and
coordination primitives in C++ while exploring concurrency.

The current code focuses on:

- A simple task queue used by a thread manager
- A thread pool that accepts `std::function<void()>` jobs
- A mutex-protected linked list of integers
- A randomized workload that submits concurrent insert and remove tasks

## Current Structure

- `threadManager` starts a fixed number of worker threads and dispatches queued
  tasks until shutdown.
- `queue` is a lightweight linked-list-backed task queue used internally by the
  thread manager.
- `linkedList` stores task pointers for the queue implementation.
- `linkedListNum` stores integers and protects the list with a single mutex.
- `utils` provides a random number helper used by the stress test.

## Learning Notes

- The code intentionally uses raw pointers in some places to make ownership and
  manual memory management visible.
- The thread pool currently owns submitted tasks and deletes them after
  execution.
- `linkedListNum` uses one mutex around the entire list, which keeps the design
  simple and easy to reason about before moving to finer-grained locking.

## Requirements

- A C++20-compatible compiler

## Build and Run

```sh
clang++ -std=c++20 main.cpp linkedList.cpp queue.cpp threadManager.cpp utils.cpp linkedListNum.cpp -o ThreadSafeDataStructure
./ThreadSafeDataStructure
```

If you prefer CMake, the repository also includes a `CMakeLists.txt` file.

## Entry Point

`main.cpp` creates a `threadManager`, runs the randomized linked-list stress
test, prints the number of tasks submitted, and then shuts the pool down.

## Next Steps

Possible follow-ups include:

- Moving task ownership to value semantics instead of raw pointers
- Making the queue itself thread-safe
- Adding copy/move rules to the owning types
- Expanding the data structure set with more concurrency experiments
