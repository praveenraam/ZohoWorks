#pragma once
#include "slab.h"
#include "dll.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {

    DLL* headerForFull;
    DLL* tailForFull;
    DLL* headerForPartial;
    DLL* tailForPartial;
    size_t object_size;

    // Cache Manager 
} SlabCache;

SlabCache* SlabCacheInit(size_t c_object_size);                                                                                                             
void SlabCacheDestroy(SlabCache* cache);
void* SlabCacheAllocate(SlabCache* cache);
void SlabCacheDeallocator(SlabCache* cache,void* ptr);
bool isDDL_ForPartialEmpty(SlabCache* cache);