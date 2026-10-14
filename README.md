*This project has been created as part of the 42 curriculum by hhurnik.*

# Philosophers

## Description

Philosophers is a multithreaded simulation of the classic Dining Philosophers problem, implemented in C.

Each philosopher is represented by a separate thread and alternates between eating, sleeping and thinking. To eat, a philosopher must acquire two forks shared with neighboring philosophers.

The project focuses on:

- multithreading with POSIX threads
- mutex-based synchronization
- shared resource management
- race-condition prevention
- timing and simulation monitoring
- avoiding deadlocks

A dedicated monitor checks whether a philosopher has exceeded `time_to_die` and stops the simulation when a death occurs or when all philosophers have reached the optional meal goal.

## Synchronization

Each fork is protected by its own mutex.

Philosophers acquire forks in different orders depending on their position at the table, reducing the risk of deadlock.

Additional mutexes protect:

- shared simulation state
- meal and death information
- console output

This ensures that philosopher state messages are printed without overlapping.

## Instructions

### Build

Clone the repository and enter the mandatory project directory:

```bash
git clone https://github.com/hhurnik/Philosophers.git
cd Philosophers/philo
make
```

This builds the executable:

```text
philo
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are expressed in milliseconds.

Arguments:

- `number_of_philosophers` — number of philosophers and forks
- `time_to_die` — maximum time a philosopher can go without starting a meal
- `time_to_eat` — time spent eating
- `time_to_sleep` — time spent sleeping
- `number_of_times_each_philosopher_must_eat` — optional number of meals each philosopher must complete before the simulation stops

### Examples

Run five philosophers:

```bash
./philo 5 800 200 200
```

Run five philosophers until each has eaten at least three times:

```bash
./philo 5 800 200 200 3
```

Single philosopher case:

```bash
./philo 1 800 200 200
```

## Project Structure

```text
Philosophers/
├── README.md
└── philo/
    ├── Makefile
    ├── philo.h
    ├── main.c
    ├── parsing.c
    ├── routine.c
    ├── monitor_death.c
    ├── monitor_simulation.c
    ├── init_mutexes.c
    ├── philo_thread_init.c
    ├── philo_thread_utils.c
    ├── sim_init_clean.c
    └── time.c
```
