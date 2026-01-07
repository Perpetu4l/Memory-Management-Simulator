# Memory Management Simulator

This project is a **terminal-based Memory Management Simulator** that demonstrates how core operating-system memory mechanisms work at a conceptual and algorithmic level.

The simulator is built for **learning and analysis**, not kernel-level execution.  

The simulator includes:

- Linear memory allocation (First Fit, Best Fit, Worst Fit)
- Buddy system allocation (power-of-two blocks)
- Two-level CPU cache hierarchy (L1 and L2)
- Virtual memory using paging and demand loading
- Page faults and page replacement
- Runtime statistics and allocator comparison

---

##  Project Structure
* `src/`  
  - `main.cpp` – Command-line interface and subsystem integration
  - `memory.cpp` – Linear memory allocation (FF/BF/WF) and fragmentation logic
  - `buddy.cpp` – Buddy system allocator implementation
  - `cache.cpp` – Multilevel cache simulation (L1, L2)
  - `vm.cpp` – Virtual memory and paging subsystem
* `include/`  
  Header files:
  - `memory.h`
  - `buddy.h`
  - `cache.h`
  - `vm.h`
* `docs/` – design + test explanations
* `tests/`  
  Input workloads used to validate different simulator features:
  - Linear allocation tests
  - Buddy allocator tests
  - Cache access tests
  - Virtual memory access tests
  - Allocation strategy comparison tests
* `Makefile`
* `output/` – generated logs (created when tests run)
* `docs/` –  design document 
* `run_tests.sh` – Linux/Mac automated test runner
* `run_tests.bat`– Windows automated test runner

---

##  How to Build and Run

### Requirements
- C++17 compiler (g++ / clang++)
- `make`

### Build
Run the following command in the root directory:
```bash
make
```
### Run the simulator
Linux / Mac
```bash
./memsim
```

Windows
```powershell
memsim.exe
```
Type commands directly in the terminal.

* Type help to see all the functions avaiable after running the simulator.

---
## Running the tests
### Manually
Linux / Mac
```bash
./memsim < test/example.txt
```
Windows
```bash
memsim.exe < test\example.txt
```
output will be in terminal
### Automated 
Linux / Mac
```bash
chmod +x run_tests.sh
./run_tests.sh
```
Windows
```bash
run_tests.bat
```
 This executes all test workloads and stores the combined results in all_tests_output.txt, while generating separate log files for each test case in the output directory.
---

 ## Features Implemented 
1. **Heap Memory Management**: First Fit, Best Fit, Worst Fit, and Buddy System.
2. **Fragmentation Analysis**: Tracks internal and external fragmentation, memory utilization, and allocation success/failure rates for different allocators.
3. **Virtual Memory System**: Implements paging-based virtual memory with per-process page tables that map virtual pages to physical frames. Page size and physical memory are user-configurable.
4. **Demand Paging and Page Fault Handling**: Pages are loaded into physical memory only when accessed, with page faults handled transparently by the simulator.
5. **Page Replacement Policy**: Uses a timestamp-based LRU policy for virtual memory page replacement to model realistic eviction behavior.
6. **Multilevel Cache Hierarchy**: Simulates a two-level CPU cache system:
   - L1 Cache  
   - L2 Cache  
   Cache size, block size, and associativity are configurable. Cache replacement uses FIFO.
7. **Allocator Strategy Comparison**: Provides a comparison mode that replays identical workloads across different allocation strategies and reports fragmentation, utilization, and allocation efficiency.
8. **Runtime Statistics and Observability**: Shows detailed statistics through dump and stats commands, including page hits and faults, frame usage, cache hits and misses, and overall memory performance metrics.
---

## Demo Video
A terminal-based demonstration of the simulator is available here:

---
## Assumptions and Design Choices
- Heap allocation and virtual memory are modeled as separate subsystems with no shared validation.
- Memory protection features such as read/write/execute permissions are not simulated.
- Pages are loaded on demand: accessing an unmapped page results in a page fault and automatic mapping (no segmentation faults).
- CPU execution is abstracted; the simulator focuses on address translation and memory flow only.
- Replacement policies are simplified: LRU for virtual memory pages and FIFO for cache blocks.

### Notes:
- All test scenarios can be reproduced using the provided test inputs.
- Logs are not tracked in version control.
- Output files are generated dynamically when test workloads are executed.