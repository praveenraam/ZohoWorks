#include "./src/headers/slaballocator.h"
#include "./src/headers/dll.h"

#include <stdio.h>

int main() {
    int object_size = 20;
    int initial_allocation_size = 16;
    void* ptrs[initial_allocation_size];

    printf("Allocating %d objects of size %d:\n", initial_allocation_size, object_size);
    for (int i = 0; i < initial_allocation_size; ++i) {
        ptrs[i] = SA_Allocater(object_size);
        printf("ptrs[%d] = %p\n", i, ptrs[i]);
    }
    
    printf("FULL : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForFull);
    printf("Partial : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForPartial);

    printf("\nFreeing first 4 objects:\n");
    for (int i = 0; i < 4; ++i) {
        SA_Deallocater(object_size, ptrs[i]);
        printf("Freed ptrs[%d] = %p\n", i, ptrs[i]);
        ptrs[i] = NULL;
    }

    printf("FULL : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForFull);
    printf("Partial : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForPartial);

    int reallocation_size = 10;
    void* new_ptrs[reallocation_size];

    printf("\nRe-allocating %d new objects of size %d:\n", reallocation_size, object_size);
    for (int i = 0; i < reallocation_size; ++i) {
        new_ptrs[i] = SA_Allocater(object_size);
        printf("new_ptrs[%d] = %p\n", i, new_ptrs[i]);
    }

    printf("FULL : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForFull);
    printf("Partial : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForPartial);
    printf("\nAll allocated pointers after re-allocation:\n");

    for (int i = 0; i < initial_allocation_size; ++i) {
        if (ptrs[i] != NULL) {
            printf("ptrs[%d] = %p\n", i, ptrs[i]);
        }
    }

    for (int i = 0; i < reallocation_size; ++i) {
        printf("new_ptrs[%d] = %p\n", i, new_ptrs[i]);
    }

    printf("FULL : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForFull);
    printf("Partial : ");
    DLL_print(getInstanceOfSA()->headerForCacheList->slabCacheInDLL->headerForPartial);

    return 0;
}
