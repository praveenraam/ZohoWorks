#pragma once
#include "slab.h"
struct DLL;

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {

    struct DLL* headerForFull;
    struct DLL* tailForFull;
    struct DLL* headerForPartial;
    struct DLL* tailForPartial;
    size_t object_size;

    // Cache Manager 
} SlabCache;

SlabCache* SlabCacheInit(size_t c_object_size);                                                                                                             
void SlabCacheDestroy(SlabCache* cache);
void* SlabCacheAllocate(SlabCache* cache);
void SlabCacheDeallocator(SlabCache* cache,void* ptr);
bool isDDL_ForPartialEmpty(SlabCache* cache);