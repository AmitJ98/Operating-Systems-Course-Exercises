# Operating Systems Course - Programming Exercises

This repository contains four comprehensive programming exercises that explore fundamental operating system concepts through hands-on implementation. Each exercise demonstrates core OS principles including memory management, concurrency, parallel processing, and system-level programming.

## 👥 Authors
- **Amit Joseph**
- **Maya Heilbrun**

## 📚 Exercise Overview

### [Ex01: Memory Benchmark & Cache Analysis](./Ex01/)
**Topic**: Memory Hierarchy Performance Analysis  
**Key Concepts**: Cache behavior, memory access patterns, latency measurement

Implements a comprehensive memory latency measurement tool that analyzes performance across different cache levels (L1, L2, L3, RAM). Compares sequential vs. random access patterns and demonstrates the impact of cache hierarchy on application performance. Also includes a file operations component showcasing basic system calls.

### [Ex02: User-Level Threads Library](./Ex02/)
**Topic**: Cooperative Multitasking Implementation  
**Key Concepts**: Thread scheduling, context switching, signal handling

Complete implementation of a user-level threading library providing cooperative multitasking functionality. Features round-robin scheduling, signal-based preemption, and context switching using `sigsetjmp`/`siglongjmp`. Demonstrates the differences between user-level and kernel-level threading approaches.

### [Ex03: MapReduce Framework](./Ex03/)
**Topic**: Parallel Data Processing  
**Key Concepts**: MapReduce paradigm, thread synchronization, parallel algorithms

Multi-threaded MapReduce framework following Google's paradigm for parallel processing of large datasets. Implements the complete Map-Shuffle-Reduce pipeline with custom barrier synchronization, thread coordination, and real-time progress monitoring. Supports generic key-value data types and scalable parallel execution.

### [Ex04: Virtual Memory Management](./Ex04/)
**Topic**: Memory Management Systems  
**Key Concepts**: Address translation, page tables, memory allocation

Implementation of a virtual memory management system with multi-level page tables, address translation, and page replacement algorithms. Demonstrates core concepts of modern OS memory management including virtual-to-physical address mapping and dynamic frame allocation.

## 🛠️ Technologies & Tools
- **Programming Language**: C/C++
- **Build Systems**: Make, CMake
- **Platform**: Unix/Linux
- **Concurrency**: POSIX threads, signals
- **Development**: System calls, low-level programming

## 🎯 Learning Outcomes

Through these exercises, we gained practical experience with:

### Concurrency & Parallelism
- Thread lifecycle management
- Synchronization primitives (mutexes, barriers, condition variables)
- Context switching and scheduling algorithms
- Signal handling and preemption

### Memory Management
- Cache hierarchy analysis and optimization
- Virtual memory system implementation
- Address translation mechanisms
- Memory allocation strategies

### System Programming
- Low-level C/C++ programming
- POSIX system calls and APIs
- Performance measurement and analysis
- Inter-process communication

### Software Engineering
- Modular design patterns
- API design and implementation
- Error handling and resource management
- Testing and validation strategies

## 🚀 Getting Started

Each exercise is self-contained with its own directory structure:

```
Os/
├── Ex01/           # Memory benchmark and cache analysis
├── Ex02/           # User-level threads library
├── Ex03/           # MapReduce framework
├── Ex04/           # Virtual memory management
├── README.md       # This overview
└── .gitignore      # Git exclusion rules
```

**To explore an exercise:**
1. Navigate to the specific exercise directory
2. Read the detailed README for that exercise
3. Follow the build instructions (typically `make`)
4. Run the examples and tests provided



---
*This repository showcases practical implementation of core operating system concepts and demonstrates proficiency in system-level programming, concurrent algorithms, and performance optimization.* 