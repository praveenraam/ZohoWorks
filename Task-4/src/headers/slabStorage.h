#pragma once
#include "pointerstack.h"

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

    PointerStack* ptrStackInSlab;    // Stack implementation for deallocated Objects
    // MemoryManage* cache_passed_memory_manager;

} SlabStorage;

SlabStorage* SlabInit(size_t c_object_size ,size_t c_memoryArraySize);
void SlabDestroy(SlabStorage* slab);
void* SlabAllocater(SlabStorage* slab);
void SlabDeallocater(SlabStorage* slab, void* ptr);
bool SlabContains(SlabStorage* slab, void* ptr);
enum StatusOfSlotsAvailable getStatus(SlabStorage* slab);