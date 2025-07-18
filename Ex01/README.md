# Ex01: Memory Benchmark & Cache Analysis

## 👥 Authors
- **Amit Joseph**
- **Maya Heilbrun**

## 📋 Overview

This exercise measures memory latency across different cache levels and implements basic file operations.

## 🎯 Objectives
- Analyze cache hierarchy performance
- Compare sequential vs. random memory access patterns
- Demonstrate file system operations

## 📁 Key Files
- `memory_latency.cpp` - Memory measurement implementation
- `measure.cpp` - Main function and utilities
- `WhatIDo` - File operations demo
- `results.png` - Performance graph

## 🔧 Usage

### Memory Benchmark
```bash
make
./measure [max_size] [factor] [repeats]
```

### File Operations
```bash
make WhatIDo
./WhatIDo [argument]
```

## 📊 Results

Our measurements show distinct performance characteristics:

| Cache Level | Size | Behavior |
|-------------|------|----------|
| **L1** | 32 KiB | Minimal latency |
| **L2** | 256 KiB | Slight increase |
| **L3** | 6 MiB | Notable increase for random access |
| **RAM** | Beyond L3 | Dramatic increase |

### Key Findings
- **Sequential access** maintains low latency due to hardware prefetching
- **Random access** shows significant performance degradation beyond cache limits
- **Cache hierarchy** directly impacts application performance

## 💡 Takeaways
Memory access patterns significantly impact performance. Understanding cache behavior is crucial for optimization. 