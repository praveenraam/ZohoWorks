#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "./slabcache.h"
#include "./dll.h"
struct DLL;

typedef struct {

    struct DLL* headerForCacheList;
    struct DLL* tailForCacheList;
    pthread_mutex_t allocator_mutex;;

} SlabAllocator;

SlabAllocator* getInstanceOfSA();
void* SA_Allocater(size_t object_size);
void SA_Deallocater(size_t object_size, void* ptr);
void* SA_Reallocater(void* from,size_t current_size,size_t new_required_size);
