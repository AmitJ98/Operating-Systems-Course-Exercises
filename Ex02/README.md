# Ex02: User-Level Threads Library

## 👥 Authors
- **Amit Joseph**
- **Maya Heilbrun**

## 📋 Overview

Implementation of a complete user-level threading library providing cooperative multitasking functionality.

## 🎯 Objectives
- Implement user-level threading system
- Learn thread scheduling and context switching
- Understand cooperative multitasking

## 📁 Key Files
- `uthreads.cpp` - Main threading library
- `uthreads.h` - Public API
- `thread.cpp/.h` - Thread class implementation

## 🔧 API

```cpp
int uthread_init(int quantum_usecs);        // Initialize library
int uthread_spawn(thread_entry_point entry); // Create thread
int uthread_terminate(int tid);             // Terminate thread
int uthread_block(int tid);                 // Block thread
int uthread_resume(int tid);                // Resume thread
int uthread_yield();                        // Yield CPU
```

## 🏗️ Architecture

### Thread States
- **RUNNING**: Currently executing
- **READY**: Waiting to be scheduled  
- **BLOCKED**: Suspended

### Key Features
- Round-robin scheduling
- Signal-based preemption (`SIGVTALRM`)
- Context switching with `sigsetjmp`/`siglongjmp`
- Stack management (4096 bytes per thread)

## 🚀 Usage Example

```cpp
void worker() {
    for (int i = 0; i < 1000; i++) {
        // Do work
        if (i % 100 == 0) uthread_yield();
    }
}

int main() {
    uthread_init(1000);  // 1ms quantum
    uthread_spawn(worker);
    return 0;
}
```

## 💡 Key Concepts
- User-level vs kernel-level threads
- Context switching mechanisms
- Signal handling for preemption
- Thread lifecycle management