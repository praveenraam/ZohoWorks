#include "./headers/slab.h"
#include <stdio.h>

Slab* SlabInit(size_t c_object_size ,size_t c_memoryArraySize) {
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
    slab->ptrStackInSlab = StackInit();
    
    return slab;
}

void SlabDestroy(Slab* slab)
{
    if(slab != NULL){
        free(slab->MemoryArray);
        StackDestroy(slab->ptrStackInSlab);
        free(slab);
    }
}

void* SlabAllocater(Slab* slab){

    if(slab->status != FULL){
        void* returnPtr;
        
        if(StackIsEmpty(slab->ptrStackInSlab)){
            if((char*)slab->FreeSlabIterPointer >= (char*)slab->MemoryArray + slab->totalMemorySizeOfArray){
                return NULL;
            }
            printf("stack is empty\n");
            returnPtr = slab->FreeSlabIterPointer;
            slab->FreeSlabIterPointer = (char*)slab->FreeSlabIterPointer + slab->objectSize;
        }
        else{
            printf("Stack is Not empty\n");
            returnPtr = StackPop(slab->ptrStackInSlab);
        }

        slab->usedMemorySizeOfArray = slab->usedMemorySizeOfArray + slab->objectSize;
        slab->status = slab->totalMemorySizeOfArray == slab->usedMemorySizeOfArray ? FULL : PARTIAL;

        printf("Memory allocated\n");
        // call memory manager add
        return returnPtr;
    }
    return NULL;
}

void SlabDeallocater(Slab* slab, void* ptr){
    int fromMemory = (char*)ptr - (char*)slab->MemoryArray;

    if(fromMemory >= 0 && fromMemory < slab->totalMemorySizeOfArray){

        if(fromMemory % slab->objectSize != 0){
            printf("Ptr is not pointing the proper memory address\n");
            return;
        }

        StackPush(slab->ptrStackInSlab,ptr);

        slab->usedMemorySizeOfArray = slab->usedMemorySizeOfArray-slab->objectSize;

        slab->status = slab->usedMemorySizeOfArray == 0 ? EMPTY : PARTIAL;

        // call memory manager remove
        printf("Memory Freed\n");
        return;

    }
    printf("Ptr is out of bound\n");
}

bool SlabContains(Slab* slab, void* ptr){
    int fromMemory = (char*)ptr - (char*)slab->MemoryArray;
    return fromMemory >= 0 && fromMemory < slab->totalMemorySizeOfArray;
}

enum StatusOfSlotsAvailable getStatus(Slab* slab){
    return slab->status;
}