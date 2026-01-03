# Memory-Management-Simulator

## Overview
This project implements a **Memory Management Simulator** that models how an
operating system manages memory. It simulates:

- Dynamic memory allocation (FF, BF, WF, Buddy)
- Multi-level CPU cache (L1 and L2)
- Virtual memory using paging
- Page faults, cache hits/misses, and fragmentation statistics

The simulator is **educational**, not a real OS kernel. It focuses on correctness,
design clarity, and trade-offs between strategies.

---

## Features

### 1. Dynamic Memory Allocation
- First Fit (FF)
- Best Fit (BF)
- Worst Fit (WF)
- Buddy System allocator
- Tracks:
  - Internal & external fragmentation
  - Memory utilization
  - Allocation success rate

### 2. Cache Simulation
- Configurable L1 and L2 caches
- Parameters:
  - Cache size
  - Block size
  - Associativity
- Tracks:
  - Cache hits and misses
  - Access penalties
  - Total memory access cycles

### 3. Virtual Memory
- Per-process page tables
- Paging-based address translation
- Page fault handling
- LRU page replacement
- Frame usage tracking per process

### 4. Statistics & Comparison
- Detailed runtime statistics
- Compare allocation strategies on the same workload

---

## Build Instructions

### Compile
```bash
make
