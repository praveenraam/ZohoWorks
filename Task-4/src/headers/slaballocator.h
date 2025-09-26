#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./slabcache.h"
#include "./dll.h"
struct DLL;

typedef struct {

    struct DLL* headerForCacheList;
    struct DLL* tailForCacheList;

} SlabAllocator;

SlabAllocator* getInstanceOfSA();
void* SA_Allocater(size_t object_size);
void SA_Deallocater(size_t object_size, void* ptr);
