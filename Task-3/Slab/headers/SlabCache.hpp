#pragma once
#include<vector>
#include"Slab.hpp"
#include "./MyClass.hpp"
#include "./HerClass.hpp"

template <typename T>
class SlabCache{
    private:
        std::vector<Slab<T>*> vectorOfSlabs;

    public:
        T* sl_allocate();
        void deallocate(T* ptr);
};

template <typename T>
T* SlabCache<T>::sl_allocate(){
    for(Slab<T>* slab : vectorOfSlabs){
        T* obj = slab->allocate();
        if (obj) return obj;
    }

    vectorOfSlabs.push_back(new Slab<T>(10));
    return vectorOfSlabs.back()->allocate();
}

template <typename T>
void SlabCache<T>::deallocate(T* ptr){
    for(auto& slab : vectorOfSlabs){
        if(slab->contains(ptr)){
            slab->deallocate(ptr);
            return;
        }
    }
}