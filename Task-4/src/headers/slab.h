#pragma once
#include <stdlib.h>

enum StatusOfSlotsAvailable{
    EMPTY,
    PARTIAL,
    FULL
};

typedef struct {

    void* MemoryArray;
    void* FreeSlabIterPointer;
    size_t memoryArraySize;
    size_t objectSize;
    size_t totalMemorySizeOfArray;
    size_t usedMemorySizeOfArray;

    enum StatusOfSlotsAvailable status;

    // Stack implementation for deallocated Objects
    // MemoryManage* cache_passed_memory_manager;

} Slab;

Slab* SlabCreate(size_t c_object_size ,size_t c_memoryArraySize);
void SlabDestroy(Slab* slab);