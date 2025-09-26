#include "./headers/dll.h"
#include "./headers/slabcache.h"

SlabCache* SlabCacheInit(size_t c_object_size){

    SlabCache* cache = (SlabCache*)malloc(sizeof(SlabCache));

    if(cache == NULL){
        return NULL;
    }

    cache->object_size = c_object_size;
    
    cache->headerForFull = NULL;
    cache->tailForFull = NULL;
    cache->headerForPartial = NULL;
    cache->tailForPartial = NULL;

    return cache;
}

void SlabCacheDestroy(SlabCache* cache){
    if(cache != NULL){
        if(cache->headerForFull != NULL) DLL_DestroyAll(cache->headerForFull);
        if(cache->headerForPartial != NULL) DLL_DestroyAll(cache->headerForPartial);
        free(cache);
    }
}

void* SlabCacheAllocate(SlabCache* cache){

    if(isDDL_ForPartialEmpty(cache)){
        Slab* newSlab = SlabInit(cache->object_size,10);
        if (newSlab == NULL) return NULL;
      
        cache->headerForPartial = DLL_Init(newSlab);
        cache->tailForPartial = cache->headerForPartial;
    }

    void* allocatedPtr = SlabAllocater(cache->headerForPartial->slabInDLL);

    if (allocatedPtr == NULL) {
        return NULL;
    }

    if(getStatus(cache->headerForPartial->slabInDLL) == FULL){
        
        DLL* oldHeader = cache->headerForPartial;
        cache->headerForPartial = cache->headerForPartial->next;

        if(cache->headerForPartial != NULL){
            cache->headerForPartial->prev = NULL;
        }
        else{
            cache->tailForPartial = NULL;
        }

        oldHeader->next = NULL;
        oldHeader->prev = NULL;

        if(cache->headerForFull == NULL){
            cache->headerForFull = oldHeader;
            cache->tailForFull = oldHeader;
            oldHeader->next = NULL;
            oldHeader->prev = NULL;
        }
        else{
            cache->tailForFull = DLL_InsertAtEnd(cache->tailForFull,oldHeader->slabInDLL);
            DLL_Destroy(oldHeader);
        }
}
    return allocatedPtr;

}

void SlabCacheDeallocator(SlabCache* cache,void* ptr){

    if (cache == NULL || ptr == NULL) return;

    DLL* current = cache->headerForPartial;
    while(current != NULL){
        if(SlabContains(current->slabInDLL,ptr)){
            SlabDeallocater(current->slabInDLL,ptr);
            return;
        }
        current = current->next;
    }

    current = cache->headerForFull;
    while(current != NULL){
        if (SlabContains(current->slabInDLL, ptr)) {
            SlabDeallocater(current->slabInDLL, ptr);

            if (getStatus(current->slabInDLL) != FULL) {

                if (current->prev != NULL) { // if not head
                    current->prev->next = current->next;
                } else { // if head
                    cache->headerForFull = current->next; 
                }

                if (current->next != NULL) { // if not tail
                    current->next->prev = current->prev;
                } else { // if tail
                    cache->tailForFull = current->prev;
                }

                current->prev = cache->tailForPartial;
                current->next = NULL;
                if (cache->tailForPartial != NULL) {
                    cache->tailForPartial->next = current;
                }
                cache->tailForPartial = current;
                if (cache->headerForPartial == NULL) {
                    cache->headerForPartial = current;
                }
            }
            return;
        }
        current = current->next;
    }
}

bool isDDL_ForPartialEmpty(SlabCache* cache){
    return cache == NULL || cache->headerForPartial == NULL;
}