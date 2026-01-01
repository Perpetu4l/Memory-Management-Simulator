#ifndef MEMORY_H
#define MEMORY_H

#include <list>
using namespace std;

struct Block {
    int start;
    int size;
    bool free;
};

void init_memory(int total_size);
void dump_memory();

int malloc_first_fit(int size);


#endif
