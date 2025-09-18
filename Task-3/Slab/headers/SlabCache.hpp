#pragma once
#include<vector>
#include"Slab.hpp"

class SlabCache{
    private:
        std::vector<Slab*> vectorOfSlabs;

    public:
        MyClass* sl_allocate(std::string name);
        void deallocate(MyClass* ptr);
};

MyClass* SlabCache::sl_allocate(std::string name){
    for(Slab* slab : vectorOfSlabs){
        MyClass* obj = slab->allocate(name);
        if (obj) return obj;
    }

    vectorOfSlabs.push_back(new Slab(10));
    return vectorOfSlabs.back()->allocate(name);
}

void SlabCache::deallocate(MyClass* ptr){
    for(auto& slab : vectorOfSlabs){
        if(slab->contains(ptr)){
            slab->deallocate(ptr);
            return;
        }
    }
}