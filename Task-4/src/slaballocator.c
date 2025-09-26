#include "./headers/slaballocator.h"

SlabAllocator* getInstanceOfSA() {
    static SlabAllocator* instance = NULL;
    if (instance == NULL) {
        instance = (SlabAllocator*)malloc(sizeof(SlabAllocator));
        if (instance != NULL) {
            instance->headerForCacheList = NULL;
            instance->tailForCacheList = NULL;
        }
    }
    return instance;
}

void* SA_Allocater(size_t object_size){

    SlabAllocator* instance = getInstanceOfSA();
    if(instance->headerForCacheList == NULL){
        SlabCache* cache = SlabCacheInit(object_size);
        instance->headerForCacheList = DLL_Init_SA(cache);
        instance->tailForCacheList = instance->headerForCacheList;
    }

    SlabCache* cache = NULL;
    DLL* current = instance->headerForCacheList;
    while(current != NULL){

        if(current->slabCacheInDLL->object_size == object_size){
            cache = current->slabCacheInDLL;
            break;
        }
        current = current->next;
    }

    if(cache == NULL){
        cache = SlabCacheInit(object_size);
        instance->tailForCacheList = DLL_InsertAtEnd_SA(instance->tailForCacheList,cache);
    }

    if (cache == NULL) {
        return NULL;
    }

    void* ptr = SlabCacheAllocate(cache);

    return ptr;
}

void SA_Deallocater(size_t object_size, void* ptr){

    SlabAllocator* instance = getInstanceOfSA();
    if(instance->headerForCacheList == NULL){
        return;
    }

    SlabCache* cache = NULL;
    DLL* current = instance->headerForCacheList;
    while(current != NULL){

        if(current->slabCacheInDLL->object_size == object_size){
            cache = current->slabCacheInDLL;
            break;
        }
        current = current->next;
    }

    if(cache == NULL){
        return;
    }

    SlabCacheDeallocator(cache,ptr);

}