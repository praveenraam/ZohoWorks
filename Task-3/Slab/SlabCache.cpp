#include "./headers/SlabCache.h"
#include "./headers/Slab.h"

template<typename T> T* SlabCache<T>::allocate(){
    for(Slab slab : vectorOfSlabs){
        T* obj = slab.allocate();
        if (obj) return obj;
    }

    vectorOfSlabs.push_back(new Slab<T>(10));
    return vectorOfSlabs.back().allocate();
}

template<typename T> void SlabCache<T>::deallocate(T* ptr){
    for(auto& slab : vectorOfSlabs){
        if(slab.contains(ptr)){
            slab.deallocate(ptr);
            return;
        }
    }
}