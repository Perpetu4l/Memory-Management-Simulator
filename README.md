# Memory-Management-Simulator

## Overview
This project implements a **Memory Management Simulator** that models how an
operating system manages memory. It simulates:
- Different memory allocation strategies (First Fit, Best Fit, Worst Fit, Buddy allocation)
- Multi-level CPU cache hierarchy (L1 and L2)
- Virtual memory using paging
- Page faults, cache hits/misses, and fragmentation statistics

The simulator is not a real OS kernel. Instead, it focuses on algorithmic
correctness, design clarity, and faithful simulation of OS-level abstractions
such as allocation strategies, page tables, cache hierarchies, and replacement
policies.


---

## Features implemented
### 1. Dynamic Memory Allocation Strategies
- First Fit, Best Fit, and Worst Fit allocation strategies.
- Buddy System allocator for power-of-two memory management.
- Dynamic allocation and deallocation with block splitting and coalescing.
- Tracking: Internal & external fragmentation, Memory utilization, Allocation success rate.
### 2. Multilevel Cache Simulation
- Configurable L1 and L2 caches with parameters - cache size, block size, associativity (direct-mapped or set-associative).
- FIFO replacement policy.
- Tracking: Cache hits and misses, Access penalties based on disk penalty, Total memory access cycles.
### 3. Virtual Memory
- Per-process page tables.
- Paging-based address translation maps virtual pages to physical frames.
- Page fault handling.
- LRU page replacement.
- Frame usage tracking per process.
### 4. Statistics & Comparison
- Detailed runtime statistics
- Compare allocation strategies on the same workload
- reports the following metrics :
    - Allocation success and failure count.
    - Memory utilization percentage, Internal fragmentation, External fragmentation.
    - Per-process physical frame usage, Page hits, page faults, and fault rate.
    - Cache hits and misses per cache level (L1, L2).
    - Total memory access cycles and penalty accumulation.
---
## Build and Run

### Prerequisites
Ensure the following tools are installed on your system:

- A C++ compiler with **C++17** support  
  - Linux: `g++`
  - macOS: `clang++` (via Xcode Command Line Tools)
  - Windows: `g++` via MinGW or WSL
- `make`

### Building the Simulator

Navigate to the root directory of the project (the directory containing the `Makefile`) and run:

```bash
make
```

### Running the Simulator

Start the interactive memory management simulator using:
On linux/macos terminal:
```bash
./memsim
```
On windows command prompt:
```powershell
memsim.exe
```

### Running Test Workloads
The `tests/` directory contains predefined input workloads.
Test files can be executed by redirecting them into the simulator. For example:

On linux/macos terminal:
```bash
./memsim < tests/test_linear_alloc.txt
```
On windows command prompt:
```powershell
memsim.exe < tests/test_linear_alloc.txt
```

Repeat the above command with other test files as needed.
