# Philosophers

A C implementation of the Dining Philosophers problem, developed as part of the 42/1337 curriculum.

## Overview

The project explores concurrent programming by simulating philosophers who alternate between eating, sleeping, and thinking while sharing forks. The goal is to manage threads and shared resources while avoiding data races and deadlocks.

## Features

- Multithreading using  threads (`pthreads`)
- Mutexes for shared resource protection
- Synchronization between threads
- Precise monitoring of philosopher states and death conditions
- Optional meal-count limits and simulation termination

## Technologies

- C
- POSIX Threads (`pthread`)
- Mutexes and synchronization
- Linux / UNIX APIs
- Makefile

## What I Learned

- Thread creation and management
- Race conditions and data protection
- Mutex locking and unlocking
- Deadlock prevention and concurrency debugging
- Coordinating shared resources in a multithreaded program

## Usage

```bash
make
./philo 5 800 200 200
```

Arguments: number of philosophers, time to die, time to eat, and time to sleep (times in milliseconds).
