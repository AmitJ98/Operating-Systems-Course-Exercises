# Ex04: Virtual Memory Management

## 👥 Authors
- **Amit Joseph**
- **Maya Heilbrun**

## 📋 Overview

Implementation of a virtual memory management system providing address translation, page table management, and memory allocation strategies.

## 🎯 Objectives
- Implement virtual-to-physical address translation
- Understand page table structures
- Learn memory allocation and page replacement

## 📁 Key Files
- `VirtualMemory.cpp/.h` - VM implementation and interface
- `PhysicalMemory.cpp/.h` - Physical memory simulation
- `MemoryConstants.h` - System constants

## 🔧 API

```cpp
void VMinitialize();                              // Initialize VM system
int VMread(uint64_t virtualAddress, word_t* value);  // Read from virtual address
int VMwrite(uint64_t virtualAddress, word_t value);  // Write to virtual address
```

## 🏗️ Architecture

### Address Translation
```
Virtual Address: | Page Number | Offset |
Physical Address: | Frame Number | Offset |
```

### Key Components
- Multi-level page tables
- Frame allocation strategy
- Page replacement algorithm
- Address space management

## 🚀 Usage Example

```cpp
#include "VirtualMemory.h"

int main() {
    VMinitialize();
    
    word_t data = 0x12345678;
    VMwrite(0x1000, data);
    
    word_t value;
    VMread(0x1000, &value);
    printf("Value: 0x%lx\n", value);
    
    return 0;
}
```

## 🔄 Translation Process
1. Extract page number from virtual address
2. Navigate page table hierarchy
3. Find physical frame
4. Handle page faults if needed

## 💡 Key Concepts
- Address translation mechanisms
- Page table design
- Memory allocation strategies
- Page replacement policies 