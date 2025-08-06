# scheduler

A lightweight scheduler implemented in C for managing and executing recurring or scheduled tasks.
This project was built for educational purposes, with the aim of being suitable for simple C-based application that requires timed job execution.

## Features

- Simple API for adding, removing, and managing scheduled tasks
- Efficient timer management for periodic or one-shot jobs
- Designed for embedded or resource-constrained environments
- Written in pure C for portability

## Getting Started

### Cloning the Repository

```sh
git clone https://github.com/OffirRokach/scheduler.git
cd scheduler
```

### Building

You can build the scheduler using your favorite C compiler. For example:

```sh
gcc -o scheduler main.c scheduler.c
```

> _Replace `main.c` and `scheduler.c` with your actual source files as needed._

### Usage

Include the scheduler header and source in your C project. Example:

```c
#include "scheduler.h"

void my_task(void *arg) {
    // Task logic here
}

int main() {
    scheduler_init();
    scheduler_add_task(1000, my_task, NULL); // Run every 1000 ms
    scheduler_start();
    return 0;
}
```

## API Reference

Document the main functions and their usage here. For example:

- `SchedulerCreate()`
- `SchedulerAdd(scheduler_t* scheduler, int (*action_func)(void* params), void* params, size_t interval_in_sec)`
- `SchedulerRemove(scheduler_t* scheduler, uid_t identifier)`
- `SchedulerClear(scheduler_t* scheduler)`
- `SchedulerRun(scheduler_t* scheduler)`
- `SchedulerStop(scheduler_t* scheduler)`
- `SchedulerDestroy(scheduler_t* scheduler)`
- `SchedulerSize(const scheduler_t* scheduler)`
- `SchedulerIsEmpty(const scheduler_t* scheduler)`

---

For more details, visit the [repository](https://github.com/OffirRokach/scheduler).
