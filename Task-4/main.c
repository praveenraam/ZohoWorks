#include "./src/headers/slab.h"
#include "./src/headers/dll.h"
#include "./src/headers/slabcache.h"

#include <stdio.h>

int main() {
    SlabCache* sc = SlabCacheInit(8);

    int allocation_size = 116;
    
    void* ptrs[allocation_size];

    printf("Allocating %d objects:\n", allocation_size);
    for (int i = 0; i < allocation_size; ++i) {
        ptrs[i] = SlabCacheAllocate(sc);
        printf("ptrs[%d] = %p\n", i, ptrs[i]);
    }

    printf("\nPartial slabs after allocation:\n");
    DLL_print(sc->headerForPartial);

    printf("Full slabs after allocation:\n");
    DLL_print(sc->headerForFull);

    printf("\nFreeing every third object:\n");
    for (int i = 0; i < allocation_size; i += 3) {
        SlabCacheDeallocator(sc, ptrs[i]);
        printf("Freed ptrs[%d] = %p\n", i, ptrs[i]);
    }

    printf("\nPartial slabs after freeing:\n");
    DLL_print(sc->headerForPartial);
    printf("Full slabs after freeing:\n");
    DLL_print(sc->headerForFull);

    printf("\nRe-allocating freed slots (not all):\n");
    for (int i = 0; i < allocation_size / 2; i += 3) {
        void* p = SlabCacheAllocate(sc);
        printf("Re-allocated ptr = %p\n", p);
    }

    printf("\nPartial slabs after partial re-allocation:\n");
    DLL_print(sc->headerForPartial);
    printf("Full slabs after partial re-allocation:\n");
    DLL_print(sc->headerForFull);

    SlabCacheDestroy(sc);
    return 0;
}