#pragma once
#include<vector>
#include"Slab.hpp"

template <typename T>
class SlabCache{
    private:
        std::vector<Slab<T>*> vectorOfSlabs;

    public:
        T* sc_allocate();
        void sc_deallocate(T* ptr);
};

template <typename T>
T* SlabCache<T>::sc_allocate(){
    for(Slab<T>* slab : vectorOfSlabs){
        if(slab->getStatus() == StatusOfSlotsAvailable::FULL) continue;
        T* obj = slab->sb_allocate();
        if (obj) return obj;
    }

    vectorOfSlabs.push_back(new Slab<T>(10));
    return vectorOfSlabs.back()->sb_allocate();
}

template <typename T>
void SlabCache<T>::sc_deallocate(T* ptr){
    for(auto& slab : vectorOfSlabs){
        if(slab->contains(ptr)){
            slab->sb_deallocate(ptr);
            return;
        }
    }
}