# Ex03: MapReduce Framework

## 👥 Authors
- **Amit Joseph**
- **Maya Heilbrun**

## 📋 Overview

Multi-threaded MapReduce framework implementation enabling parallel processing of large datasets through the Map-Shuffle-Reduce pipeline.

## 🎯 Objectives
- Implement MapReduce programming model
- Learn parallel processing and synchronization
- Practice thread coordination

## 📁 Key Files
- `MapReduceFramework.cpp` - Core implementation
- `MapReduceFramework.h` - Public API
- `Barrier.cpp/.h` - Synchronization barrier

## 🔧 API

```cpp
JobHandle startMapReduceJob(const MapReduceClient& client,
                           const InputVec& inputVec, 
                           OutputVec& outputVec,
                           int multiThreadLevel);

void getJobState(JobHandle job, JobState* state);
void waitForJob(JobHandle job);
void closeJobHandle(JobHandle job);
```

## 🏗️ Pipeline

1. **Map Phase**: Transform input into key-value pairs
2. **Shuffle Phase**: Group pairs by key 
3. **Reduce Phase**: Process grouped data

## 🚀 Usage Example

```cpp
class WordCountClient : public MapReduceClient {
    void map(const K1* key, const V1* value, void* context) const override {
        // Split text, emit words
        emit2(word, count, context);
    }
    
    void reduce(const IntermediateVec* pairs, void* context) const override {
        // Sum counts, emit result
        emit3(word, total_count, context);
    }
};

// Usage
WordCountClient client;
JobHandle job = startMapReduceJob(client, input, output, 4);
waitForJob(job);
```

## 🧵 Synchronization
- Custom `Barrier` class for phase transitions
- Mutex protection for shared data
- Thread-safe progress monitoring

## 💡 Key Concepts
- Parallel programming patterns
- Thread synchronization primitives
- Load balancing strategies
- MapReduce paradigm