#include "./headers/slab.h"

Slab* SlabCreate(size_t c_object_size ,size_t c_memoryArraySize) {
    Slab* slab = (Slab*)malloc(sizeof(Slab));

    if(slab == NULL) {
        return NULL;
    }

    slab->memoryArraySize = c_memoryArraySize;
    slab->objectSize = c_object_size;
    slab->totalMemorySizeOfArray = c_memoryArraySize*c_object_size;
    slab->usedMemorySizeOfArray = 0;

    slab->MemoryArray = malloc(slab->totalMemorySizeOfArray);
    if(slab->MemoryArray == NULL){
        free(slab);
        return NULL;
    }

    slab->FreeSlabIterPointer = slab->MemoryArray;
    slab->status = EMPTY;

    return slab;
}

void SlabDestroy(Slab* slab)
{
    if(slab != NULL){
        free(slab->MemoryArray);
        free(slab);
    }
}

void* SlabAllocater(Slab* slab){
    return NULL;
}

void SlabDeallocater(Slab* slab, void* ptr){
    return;
}

bool SlabContains(Slab* slab, void* ptr){
    return true;
}

enum StatusOfSlotsAvailable getStatus(Slab* slab){
    return FULL;
}