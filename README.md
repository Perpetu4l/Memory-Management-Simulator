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

## Project Structure

- `src/`  
  - `memory.cpp` – Linear memory allocation (FF/BF/WF) and fragmentation logic
  - `buddy.cpp` – Buddy system allocator implementation
  - `cache.cpp` – Multilevel cache simulation (L1, L2)
  - `vm.cpp` – Virtual memory and paging subsystem
  - `main.cpp` – Command-line interface and subsystem integration

- `include/`  
  Header files:
  - `memory.h`
  - `buddy.h`
  - `cache.h`
  - `vm.h`

- `tests/`  
  Input workloads used to validate different simulator features:
  - Linear allocation tests
  - Buddy allocator tests
  - Cache access tests
  - Virtual memory access tests
  - Allocation strategy comparison tests

- `memsim`  
  Compiled simulator executable generated after build

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

---

## Demo Video


https://github.com/user-attachments/assets/33a4c798-d4b9-4929-9a67-8d73b0383502


---

## Simulation Scope and Technical Notes

This project is designed as an **educational memory management simulator**, implemented entirely in user space.  
It aims to model the **core mechanisms and control flow** of memory management systems, rather than enforcing all correctness and protection guarantees expected from a real operating system kernel.

The following points describe the scope, assumptions, and intentional simplifications of the simulator.

### Memory Allocation vs Virtual Memory

The simulator treats **heap allocation** (First Fit, Best Fit, Worst Fit, Buddy) and **virtual memory paging** as logically separate subsystems.

- Heap allocation manages a simulated contiguous physical memory region and tracks block ownership and fragmentation.
- Virtual memory operates independently through per-process page tables and frame allocation.

As a result, virtual memory accesses do **not** verify whether a given address was previously allocated via the heap allocator.  
This design choice avoids tightly coupling heap metadata with page table logic and allows the simulator to focus on address translation behavior.

---

### Address Translation Behavior

Virtual memory follows a paging-based translation model:
Virtual Address → Page Table Lookup → Physical Address → Cache → Main Memory


When a virtual page is accessed:
- If the page is already mapped, the access is treated as a page hit.
- If the page is unmapped, the access triggers a page fault and a physical frame is assigned automatically.

Invalid memory accesses therefore do **not** raise segmentation faults, unlike real operating systems.  
All valid virtual pages within a process’s declared virtual address space are eligible for demand paging.

---

### Page Replacement and Frame Management

- Physical memory is divided into fixed-size frames derived from the configured page size.
- Page replacement is implemented using a **timestamp-based least-recently-used (LRU) policy**.
- On eviction, the victim page is invalidated in its owning process’s page table before the frame is reused.

The simulator tracks page hits, page faults, and per-process frame usage for observability and analysis.

---

### Cache and Timing Model

The cache hierarchy is simulated independently of allocation and paging logic.

- L1 and L2 caches are modeled as set-associative caches with FIFO replacement.
- Cache behavior is driven purely by physical addresses produced after page translation.
- Memory access latency is represented using fixed symbolic penalties for:
  - L1 cache access
  - L2 cache access
  - Main memory access
  - Disk access on page faults

These penalties are **illustrative**, not hardware-accurate, and exist to highlight relative performance effects.

---

### Omitted Hardware-Level Features

To maintain clarity and modularity, the simulator does not model:
- CPU instruction execution or pipelines
- Hardware privilege levels
- Read/Write/Execute permission bits
- TLBs or interrupt handling
- True concurrency or preemption

These omissions are intentional and keep the simulator focused on **memory management algorithms and data structures**, rather than full OS behavior.

---

Overall, the simulator prioritizes **algorithmic transparency, correctness of control flow, and measurable behavior** over low-level fidelity.  
All simplifications are deliberate and documented to ensure the system remains predictable, explainable, and suitable for academic exploration.
