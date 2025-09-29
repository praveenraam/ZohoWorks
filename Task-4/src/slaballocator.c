#include "./headers/slaballocator.h"
#include <string.h>

SlabAllocator* getInstanceOfSA() {
    static SlabAllocator* instance = NULL;
    if (instance == NULL) {
        instance = (SlabAllocator*)malloc(sizeof(SlabAllocator));
        if (instance != NULL) {
            instance->headerForCacheList = NULL;
            instance->tailForCacheList = NULL;

            pthread_mutex_init(&instance->allocator_mutex, NULL);
        }
    }
    return instance;
}

void* SA_Allocater(size_t object_size){

    SlabAllocator* instance = getInstanceOfSA();

    pthread_mutex_lock(&instance->allocator_mutex);

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

    pthread_mutex_unlock(&instance->allocator_mutex);

    if (cache == NULL) {
        return NULL;
    }

    void* ptr = SlabCacheAllocate(cache);

    return ptr;
}

void SA_Deallocater(size_t object_size, void* ptr){

    SlabAllocator* instance = getInstanceOfSA();

    pthread_mutex_lock(&instance->allocator_mutex);

    if(instance->headerForCacheList == NULL){
        pthread_mutex_unlock(&instance->allocator_mutex);
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
        pthread_mutex_unlock(&instance->allocator_mutex);
        return;
    }
    pthread_mutex_unlock(&instance->allocator_mutex);

    SlabCacheDeallocator(cache,ptr);

}

void* SA_Reallocater(void* from_address, size_t current_size, size_t new_required_size)
{
    if(new_required_size == 0){
        SA_Deallocater(current_size,from_address);
        return NULL;
    }

    if(from_address == NULL){
        return SA_Allocater(new_required_size);
    }

    void* new_address = SA_Allocater(new_required_size);

    if(new_address == NULL) return NULL;

    size_t copy_size = new_required_size < current_size ? new_required_size : current_size;
    memcpy(new_address,from_address,copy_size);

    SA_Deallocater(current_size,from_address);
    return new_address;
}