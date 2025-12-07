# Priority Queue with Aging

A custom implementation of Priority Queue with Aging mechanism in C++ for educational purposes.

## Project Overview

This project demonstrates the implementation of **Priority Queue** and **Aging** technique, two important concepts in operating system CPU scheduling, using C++.

### Key Features

- **Custom Min-Heap Implementation**: Built from scratch without using `std::priority_queue`
- **Aging Mechanism**: Dynamic priority adjustment based on waiting time
- **Starvation Prevention**: Ensures low-priority processes eventually get executed
- **Real-time Visualization**: Live scheduling process display in console
- **Statistical Analysis**: Average waiting time, turnaround time, CPU utilization, and more

## Core Concepts

### Priority Queue

- Each element has a priority; higher priority elements are processed first
- Min-Heap based implementation (lower value = higher priority)
- Insert/Delete: O(log n)

### Aging Technique

**Problem**: **Starvation** in priority scheduling
- Low-priority processes may wait indefinitely

**Solution**: Gradually increase priority based on waiting time

```
effective_priority = base_priority - (waiting_time × aging_factor)
```

## Project Structure

```
aging/
├── include/            # Header files
│   ├── Process.h
│   ├── PriorityQueue.h
│   ├── Scheduler.h
│   ├── Statistics.h
│   └── Visualizer.h
├── src/               # Source files
│   ├── Process.cpp
│   ├── PriorityQueue.cpp
│   ├── Scheduler.cpp
│   ├── Statistics.cpp
│   └── Visualizer.cpp
├── tests/             # Test files
├── bin/               # Executables
├── obj/               # Object files
├── main.cpp           # Main program
├── Makefile           # Build system
└── README.md
```

## Build and Run

### Requirements

- C++17 compatible compiler (g++, clang++, MSVC)
- Make (build system)

### Build

```bash
# Basic build
make

# Debug build
make debug

# Release build (optimized)
make release

# Clean build
make clean
make
```

### Run

```bash
# Build and run
make run

# Or run directly
./bin/aging_demo.exe
```

## Demo Scenarios

### Scenario 1: Without Aging (Starvation Demo)

```
Aging Factor: 0.0
Result: Only high-priority processes execute, low-priority wait indefinitely
```

### Scenario 2: With Aging (Starvation Prevention)

```
Aging Factor: 0.1 (Conservative)
Result: Priority increases based on waiting time, all processes execute
```

### Scenario 3: Aggressive Aging

```
Aging Factor: 0.5 (Aggressive)
Result: Rapid priority increase, more balanced execution order
```

### Scenario 4: Random Processes (Large Scale)

```
Generate and schedule 15 random processes
```

### Scenario 5: Real-time Visualization

```
Step-by-step real-time visualization of scheduling process
```

### Scenario 6: Aging Factor Comparison

```
Performance comparison across different aging factor values
```

## Main Classes

### Process

Process/Task representation

```cpp
- id: Process identifier
- base_priority: Original priority
- effective_priority: Priority after aging
- arrival_time: Arrival time
- burst_time: Execution time
- waiting_time: Time spent waiting
```

### PriorityQueue

Custom Min-Heap with aging support

```cpp
- insert(): Insert process
- extractMin(): Extract highest priority process
- applyAging(): Apply aging to all processes
- rebuildHeap(): Rebuild heap property
```

### Scheduler

Simulation orchestrator

```cpp
- run(): Execute non-preemptive scheduling
- generateRandomProcesses(): Generate random processes
- displayStatistics(): Display statistics
- displayGanttChart(): Show Gantt chart
```

### Statistics

Performance metrics tracking

```cpp
- Average waiting time
- Average turnaround time
- Average response time
- CPU utilization
- Aging event count
```

### Visualizer

Console output utilities

```cpp
- Display queue status
- Output process information
- Generate Gantt chart
- Show progress indicators
```

## Algorithms

### Aging Application

```cpp
for each process in heap:
    waiting_time = current_time - arrival_time - execution_time
    effective_priority = base_priority - (waiting_time × aging_factor)
    effective_priority = max(0.0, effective_priority)

rebuild_heap()  // Maintain heap property
```

### Scheduler Execution (Non-Preemptive)

```cpp
while (has_processes OR !queue.isEmpty()):
    add_arrived_processes_to_queue()

    if (!queue.isEmpty()):
        process = queue.extractMin()
        execute_process_fully()

        during_execution:
            queue.applyAging()       // Age waiting processes
            display_queue_state()    // Visualization
    else:
        current_time++  // CPU idle
```

## Aging Factor Tuning

| Aging Factor | Description | Characteristics |
|--------------|-------------|-----------------|
| 0.0 | No Aging | Starvation possible |
| 0.05 | Very Conservative | Slow priority increase |
| 0.1 | Conservative (Recommended) | Balanced scheduling |
| 0.2 | Aggressive | Fast priority increase |
| 0.5 | Very Aggressive | Nearly FCFS |

## Learning Objectives

What you can learn from this project:

1. **Data Structures**: Custom Heap implementation and maintenance
2. **Algorithms**: Dynamic priority adjustment, Heap operations
3. **C++ Programming**:
   - Object-oriented design
   - Memory management (pointers, destructors)
   - STL container usage
4. **Operating Systems**: CPU scheduling, Starvation problem
5. **System Programming**: Simulation system implementation
6. **Software Engineering**: Modular design, testing

## Example Statistics Output

```
============================================================
                    STATISTICS REPORT
============================================================
  Total Processes:          5
  Completed Processes:      5
  Total Execution Time:     17 time units
------------------------------------------------------------
  Average Waiting Time:     6.20 time units
  Average Turnaround Time:  9.60 time units
  Average Response Time:    6.20 time units
  Maximum Waiting Time:     12 time units
------------------------------------------------------------
  CPU Utilization:          100.00%
  Total Aging Events:       31
============================================================
```

## Future Extensions (Optional)

Ideas for further learning:

- [ ] Preemptive scheduling (Time Quantum)
- [ ] Various aging strategies (Exponential, Logarithmic)
- [ ] Multi-level Feedback Queue
- [ ] GUI visualization (SFML, Qt)
- [ ] File I/O (Process definition files)
- [ ] Performance benchmarking suite
- [ ] Unit tests (Google Test)

## License

Free to use for educational purposes.

## Author

Priority Queue + Aging Implementation (2025)
