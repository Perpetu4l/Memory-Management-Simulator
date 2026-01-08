# Memory Management Simulator — Design Document

## 1. Memory Layout & Assumptions
Physical memory is modeled as a contiguous array divided into fixed‑size frames.  
Virtual memory provides each  process with its own address space, and
page tables map virtual pages to physical frames.

**Assumptions**

- fixed page/frame size   
- demand‑paging: pages are created on first access (page fault)  


Virtual Addr → Page Table → Physical Addr → Cache → Main Memory


---

## 2. Linear allocation strategies (First_fit, Best_Fit, Worst_Fit)

A free‑list tracks blocks inside a simulated heap. Free contiguous memory is grouped as required. If no block present of size >= required size, allocation fails

| Strategy   | Description                         | 
|------------|-------------------------------------|
| First Fit  | first block large enough            |
| Best Fit   | smallest block that fits            |
| Worst Fit  | largest available block             |




Fragmentation and utilization statistics are present in comparision table.
<table>
<tr>
  <td>
    <img width="638" height="720" alt="Screenshot 2026-01-08 at 12 09 21 PM" src="https://github.com/user-attachments/assets/813f5faf-7b9f-4066-95c5-d604967d3704" />
  </td>

  <td>
    <img width="551" height="572" alt="Screenshot 2026-01-08 at 12 10 03 PM" src="https://github.com/user-attachments/assets/2054211d-a04f-42f1-814d-0b3ed6a48498" />
  </td>
</tr>
</table>

---

## 3. Buddy System Allocation strategies
Memory is divided into **power‑of‑two** sized blocks. Free contiguous memory is grouped together as required. If no block present of >= required size, allocation fails


**Algorithm**

1. round request to the nearest power‑of‑two  
2. Split larger blocks recursively  
3. On 'free', merge buddies whenever both are free  

 fast split/merge, zero external fragmentation  
 possible internal fragmentation

<p align="center">
  <img width="961" height="673" alt="Screenshot 2026-01-08 at 12 11 26 PM" src="https://github.com/user-attachments/assets/9ed02f90-df85-4fb8-b158-74a70c9d7695" />
</p>

---

## 4. Compare Mode (Allocation Strategy Comparison)

The simulator can replay the same workload under multiple strategies  
(**FF, BF, WF, Buddy**) and report statistics 

- allocation successes / failures  
- memory utilization  
- internal / external fragmentation  
- total allocations and frees  

This mode does not change allocator behavior — it only **evaluates** it.
<p align="center">
<img width="1028" height="713" alt="Screenshot 2026-01-08 at 12 41 24 PM" src="https://github.com/user-attachments/assets/fc44d423-1c4b-4f22-9edc-c8f37b7de9d2" />

</p>


---


## 4. Cache Hierarchy & Replacement
Two‑level cache model:

- **L1** — small & fast  
- **L2** — larger & slower  

Lookup order:

L1 → L2 → Main Memory

Replacement policy: **FIFO**.  

We track:

- cache hits / misses  
- main‑memory accesses  
- symbolic cycle cost (illustrative, not hardware‑accurate)

Spatial locality appears naturally because entire blocks are fetched per access.
<table>
<tr>
  <td>
    <img width="837" height="877" alt="Screenshot 2026-01-08 at 12 23 11 PM" src="https://github.com/user-attachments/assets/42110455-d0d9-4b97-a159-fe94a61eee92" />
  </td>

  <td>
  <img width="609" height="345" alt="Screenshot 2026-01-08 at 12 23 26 PM" src="https://github.com/user-attachments/assets/0e7f92fa-c2d0-4913-93bd-9be12b729caa" />
  </td>
</tr>
</table>

---

## 5. Virtual Memory Model
Paging maps virtual pages to physical frames.

**Access flow**

1. compute page number + offset  
2. page‑table lookup  
3. if missing → page fault  
4. allocate a frame and install the mapping  

Page replacement uses **LRU**.  
We track page hits, faults, and per‑process frame usage.
<table>
<tr>
  <td>
    <img width="834" height="995" alt="Screenshot 2026-01-08 at 12 36 10 PM" src="https://github.com/user-attachments/assets/cfbbdd4d-1143-46ed-bdd2-80cee3ce3749" />

  </td>

  <td>
   <img width="545" height="280" alt="Screenshot 2026-01-08 at 12 36 16 PM" src="https://github.com/user-attachments/assets/cdc89ca2-c583-4e59-a096-1a5b1ad0ea4a" />

    
  </td>
</tr>
</table>

---

## 6. Address Translation Flow

        ┌──────────────────┐
        │ Virtual Address  │
        └─────────┬────────┘
                  ↓
        ┌──────────────────┐
        │ Split Address    │
        │ (Page | Offset)  │
        └─────────┬────────┘
                  ↓
        ┌──────────────────┐
        │ Page Table Check │
        └─────────┬────────┘
             valid?
          ┌────────┴────────┐
         YES               NO
          |                 |
          |        ┌──────────────────┐
          |        │ Page Fault Trap  │
          |        │ (LRU Eviction /  │
          |        │  Free Frame)     │
          |        └─────────┬────────┘
          |                  ↓
          └──────────────► Physical Frame
                              ↓
                    ┌──────────────────┐
                    │ Cache Hierarchy  │
                    │ (L1 → L2)        │
                    └─────────┬────────┘
                         hit?
                    ┌─────────┴─────────┐
                   YES                 NO
                    |                   |
           ┌────────────────┐   ┌────────────────┐
           │ Serve from     │   │ Access Main    │
           │ Cache          │   │ Memory         │
           └────────┬───────┘   └────────┬───────┘
                    └──────────────► Data to CPU


---

## 7. Project file structure

.
├── all_tests_output.txt          # Combined output from running all tests
├── demo_video.mp4                # Terminal demo showing simulator features
├── docs
│   └── design_document.md        
├── include
│   ├── buddy.h                  
│   ├── cache.h                 
│   ├── memory.h                
│   └── vm.h                     
├── LICENSE                       
├── Makefile                      # Build automation
├── memsim                        # Compiled simulator executable
├── output
│   ├── buddy_log.txt             # Buddy allocator execution log
│   ├── cache_log.txt             # Cache hit/miss log
│   ├── compare_log.txt           # Allocation strategy comparison results
│   ├── linear_log.txt            # Linear allocator execution log
│   └── vm_log.txt                # Virtual memory & page fault log
├── README.md                    
├── run_tests.bat                 # Windows script to run all tests
├── run_tests.sh                  # Linux/Mac script to run all tests
├── src
│   ├── buddy.cpp                 # Buddy allocator implementation
│   ├── cache.cpp                 # Cache simulation implementation
│   ├── main.cpp                  # Entry point & command dispatcher
│   ├── memory.cpp                # Linear allocators implementation
│   └── vm.cpp                    # Virtual memory & paging logic
└── test
    ├── test_buddy.txt             # Buddy allocator test workload
    ├── test_cache_access.txt      # Cache access pattern test
    ├── test_compare_alloc_strats.txt # FF vs BF vs WF vs Buddy comparison test
    ├── test_linear_alloc.txt      # Linear allocator behavior test
    └── test_vm_acces.txt          # Virtual memory & page fault test


---

## 8. Limitations & Simplifications

* Implicit demand paging: unmapped pages trigger a page fault and are automatically mapped (no segmentation faults).
* Heap & paging are independent: allocators manage heap; paging manages frames/page tables separately.
* No protection bits: R/W/X permissions are not simulated.
* Abstracted CPU behavior: we model translation flow, not full instruction execution or traps.
* Simplified replacement: LRU for pages, FIFO for cache (no dirty‑bit/disk writes).

---

## 9. Testing & Validation

  I did the following tests

- allocation & fragmentation  
- buddy split/merge behavior  
- page faults vs. hits  
- cache hit/miss patterns  
- strategy comparison  

Outputs go to `output/`, while combined results go in all_tests_output.txt.
I manually verified the outputs of test cases, and they are valid.

Screenshots and the demo video, and output files explained the correctness of test cases.

---

## 10. Conclusion
I implemented the memory management simulator, including buddy systems, linear allocation, cache, and virtual memory. I added the test cases and their results. I verified all of them were correct showing correct implementation.
